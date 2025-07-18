#include "game.hpp"

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include "game_object.hpp"
#include "resource_manager.hpp"

Game::Game(unsigned int width, unsigned int height)
	: width(width), height(height) {
}

void Game::Init() {
	// load shaders
	ResourceManager::LoadShader("sprite", "src/shaders/sprite.vs", "src/shaders/sprite.frag");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	Shader& spriteShader = ResourceManager::GetShader("sprite");
	spriteShader.Use();
	spriteShader.SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);
	// set render-specific controls
	renderer = new SpriteRenderer();
	// load textures
	ResourceManager::LoadTexture("ball", "textures/circle.dds");
	ResourceManager::LoadTexture("plane-h", "textures/plane-h.dds");
	ResourceManager::LoadTexture("plane-v", "textures/plane-v.dds");

	//TODO: add another constructor for static objects
	auto planeTexH = ResourceManager::GetTexture("plane-h");
	auto planeTexV = ResourceManager::GetTexture("plane-v");
	auto planeShader = ResourceManager::GetShader("sprite");
	container.emplace_back(glm::vec2(0, height - 40), glm::vec2(width, 20), AABB, planeTexH, planeShader);
	container.emplace_back(glm::vec2(0, height / 3.0f - 20), glm::vec2(20, height * (2.0f / 3.0f)), AABB, planeTexV, planeShader);
	container.emplace_back(glm::vec2(width - 20, height / 3.0f - 20), glm::vec2(20, height * (2.0f / 3.0f)), AABB, planeTexV, planeShader);
	for (GameObject& c : container) {
		c.Physics->Static = true;
	}
}

void Game::ProcessInput(float dt) {
	if (Keys[GLFW_KEY_N]) {
		makeBall(glm::vec2(width / 2, height / 10),
				 glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX),
				 glm::vec2(0, 0));
		// only want one ball per key press
		Keys[GLFW_KEY_N] = false;
	}
	if (Keys[GLFW_KEY_M]) {
		makeBall(glm::vec2(width - 100, height - 100),
				 glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX),
				 glm::vec2(-15, 15));
		// only want one ball per key press
		Keys[GLFW_KEY_M] = false;
	}
	// if there is a selected ball and the mouse pointer is no longer over it, deselect it
	if (selectedBall && !MouseButtons[GLFW_MOUSE_BUTTON_LEFT]) {
		if (!(selectedBall->BoundingVolume->DetectMouseOver(MousePos))) {
			selectedBall->Render->Color -= glm::vec3(0.1);
			selectedBall = nullptr;
		}
	}
	// if no ball currently selected, select a ball which is over the mouse pointer
	// loop through balls in reverse order, so as to pick the one on top (drawn last) if any overlap
	if (!selectedBall) {
		for (int i = balls.size() - 1; i >= 0; i--) {
			auto& ball = balls[i];
			if (ball.BoundingVolume->DetectMouseOver(MousePos)) {
				selectedBall = &ball;
				// make selected ball brighter
				ball.Render->Color += glm::vec3(0.1);
				// only select one ball
				break;
			}
		}
	}
}

// TODO: make movement fps independent!!!
// FIXME: stop rendering/updating balls once they leave the frame!!
void Game::Update(float dt) {
	// if there is a selected ball and the mouse is down, make it follow the mouse pointer
	if (selectedBall && MouseButtons[GLFW_MOUSE_BUTTON_LEFT]) {
		selectedBall->transform->Position += ChangeInMousePos;
		// make sure gravity and any other forces don't affect its position
		selectedBall->Physics->ClearVelocity();
	}

	std::vector<CollisionInfo> collisions;
	if (balls.size() > 0) {
		// move balls[0]
		if (!(&balls.at(0) == selectedBall && MouseButtons[GLFW_MOUSE_BUTTON_LEFT])) {
			balls.at(0).Physics->ResolveForces(dt);
		}
		// for each distinct pair of balls
		for (int i = 0; i < (int)balls.size(); i++) {
			if (balls.size() > 1) {
				for (int j = i + 1; j < (int)balls.size(); j++) {
					// move every ball from balls[1] to balls[size]
					// only moved if i == 0 as we only want to move balls once (on first iteration)
					if (i == 0) {
						if (!(&balls.at(j) == selectedBall && MouseButtons[GLFW_MOUSE_BUTTON_LEFT])) {
							balls.at(j).Physics->ResolveForces(dt);
						}
					}
					// check collisions
					if (i == j) continue;
					CollisionPoints points = balls.at(i).BoundingVolume->DetectCollision(*balls.at(j).BoundingVolume);
					if (points.HasCollision) {
						collisions.emplace_back(&balls.at(i), &balls.at(j), points);
					}
				}
			}
			// collide with container
			for (GameObject& c : container) {
				CollisionPoints points = balls.at(i).BoundingVolume->DetectCollision(*c.BoundingVolume);
				if (points.HasCollision) {
					collisions.emplace_back(&balls.at(i), &c, points);
				}
			}
			// TODO: extend bounding tubes here???
		}

		//solve collisions
		for (CollisionInfo collision : collisions) {
			collision.A->Physics->ResolveCollision(*collision.B->Physics, collision.points);
		}
	}
}

void Game::Render() {
	for (GameObject& ball : balls) {
		renderer->DrawSprite(*ball.Render);
	}
	for (GameObject& c : container) {
		renderer->DrawSprite(*c.Render);
	}
}

GameObject& Game::makeBall(glm::vec2 center, glm::vec3 color, glm::vec2 velocity) {
	auto ballTex = ResourceManager::GetTexture("ball");
	auto ballShader = ResourceManager::GetShader("sprite");
	float diameter = 50.0f;
	glm::vec2 pos = center - glm::vec2(diameter / 2.0f);

	if (selectedBall) {
		int selectedLoc = 0;
		for (int i = 0; i < (int)balls.size(); i++) {
			if (&balls.at(i) == selectedBall) {
				selectedLoc = i;
				selectedBall = nullptr;
			}
		}
		balls.emplace_back(pos, glm::vec2(diameter), CIRCLE, ballTex, ballShader, 1.0f, velocity, color);
		selectedBall = &balls.at(selectedLoc);
	} else
		balls.emplace_back(pos, glm::vec2(diameter), CIRCLE, ballTex, ballShader, 1.0f, velocity, color);
	return balls.back();
}
