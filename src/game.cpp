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
	renderer = new SpriteRenderer(spriteShader);
	// load textures
	ResourceManager::LoadTexture("ball", "textures/circle.dds");
	ResourceManager::LoadTexture("plane", "textures/plane.dds");

	//TODO: initialise bounding boxes???
	//TODO: add another constructor for static objects
	auto planeTex = ResourceManager::GetTexture("plane");
	//FIXME: make sure this is ok?
	container = new GameObject(glm::vec2(0, height / 2), glm::vec2(width, height), AABB, *renderer, planeTex);
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
	// if there is a selected ball and the mouse button is no longer held, deselect it
	if (selectedBall && !MouseButtons[GLFW_MOUSE_BUTTON_LEFT]) {
		if (!selectedBall->BoundingVolume->DetectMouseOver(MousePos)) {
			selectedBall->Render.Color -= glm::vec3(0.1);
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
				ball.Render.Color += glm::vec3(0.1);
				// only select one ball
				break;
			}
		}
	}
}

//TODO: make movement fps independent!!!
void Game::Update(float dt) {
	// if there is a selected ball and the mouse is down, make it follow the mouse pointer
	if (selectedBall && MouseButtons[GLFW_MOUSE_BUTTON_LEFT]) {
		selectedBall->transform.Position += ChangeInMousePos;
		// make sure gravity and any other forces don't affect its position
		selectedBall->Physics.ClearVelocity();
	}

	std::vector<CollisionInfo> collisions;
	if (balls.size() > 0) {
		// move balls[0]
		auto& ball = balls[0];
		if (!(&ball == selectedBall && MouseButtons[GLFW_MOUSE_BUTTON_LEFT])) {
			// ball.Physics.AddForce(gravity * ball.Mass);
			ball.Physics.ResolveForces(dt);
			ball.Physics.ClearForces();
		}
		// for each distinct pair of balls
		for (int i = 0; i < (int)balls.size(); i++) {
			for (int j = i + 1; j < (int)balls.size(); j++) {
				// move every ball from balls[1] to balls[size]
				// only moved if i == 0 as we only want to move balls once (on first iteration)
				if (i == 0) {
					auto& ball = balls[j];
					if (!(&ball == selectedBall && MouseButtons[GLFW_MOUSE_BUTTON_LEFT])) {
						// ball.Physics.AddForce(gravity * ball.Mass);
						ball.Physics.ResolveForces(dt);
						ball.Physics.ClearForces();
					}
				}
				// check collisions
				CollisionPoints points = balls[i].BoundingVolume->DetectCollision(*balls[j].BoundingVolume);
				if (points.HasCollision) {
					collisions.emplace_back(&balls[i], &balls[j], points);
				}
			}
			// collide with container
			CollisionPoints points = balls[i].BoundingVolume->DetectCollision(*container->BoundingVolume);
			if (points.HasCollision) {
				collisions.emplace_back(&balls[i], container, points);
			}
			// TODO: extend bounding tubes here
			for (auto collision : collisions) {
				collision.A->Render.Color = glm::vec3(0);
				collision.B->Render.Color = glm::vec3(0);
			}
		}

		//solve collisions
	}
}

void Game::Render() {
	for (auto& ball : balls) {
		ball.Render.Draw();
	}
	container->Render.Draw();
}

GameObject& Game::makeBall(glm::vec2 center, glm::vec3 color, glm::vec2 velocity) {
	auto ballTex = ResourceManager::GetTexture("ball");
	float diameter = 50.0f;
	glm::vec2 pos = center - glm::vec2(diameter / 2.0f);
	balls.emplace_back(pos, glm::vec2(diameter), CIRCLE, *renderer, ballTex, 1.0f, velocity, color);
	return balls.back();
}
