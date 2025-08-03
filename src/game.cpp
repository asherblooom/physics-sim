#include "game.hpp"

#include <GLFW/glfw3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <imgui/misc/cpp/imgui_stdlib.h>
#include <algorithm>
#include <charconv>
#include <cstdio>
#include <iostream>

#include "game_object.hpp"
#include "render/circle_renderer.hpp"
#include "resource_manager.hpp"

Game::Game(unsigned int width, unsigned int height)
	: width(width), height(height) {}

void Game::Init() {
	ResourceManager::LoadShader("sprite", "src/shaders/sprite.vert", "src/shaders/sprite.frag");
	ResourceManager::LoadShader("circle", "src/shaders/sprite.vert", "src/shaders/circle.frag");

	glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);
	Shader& spriteShader = ResourceManager::GetShader("sprite");
	Shader& ballShader = ResourceManager::GetShader("circle");
	ballShader.Use();
	ballShader.SetMatrix4("projection", projection);
	spriteShader.Use();
	spriteShader.SetMatrix4("projection", projection);

	renderer = new SpriteRenderer(spriteShader);
	circleRenderer = new CircleRenderer(ballShader);

	// load textures
	ResourceManager::LoadTexture("ball", "textures/circle.dds");
	ResourceManager::LoadTexture("plane-h", "textures/plane-h.dds");
	ResourceManager::LoadTexture("plane-v", "textures/plane-v.dds");

	// TODO: add another constructor for static objects
	auto planeTexH = ResourceManager::GetTexture("plane-h");
	auto planeTexV = ResourceManager::GetTexture("plane-v");
	container.emplace_back(glm::vec2(0, height - 40), glm::vec2(width, 20), AABB, planeTexH);
	container.emplace_back(glm::vec2(0, height / 3.0f - 20), glm::vec2(20, height * (2.0f / 3.0f)), AABB, planeTexV);
	container.emplace_back(glm::vec2(width - 20, height / 3.0f - 20), glm::vec2(20, height * (2.0f / 3.0f)), AABB, planeTexV);
	for (GameObject& c : container) {
		c.Physics->Static = true;
	}
}

void Game::ProcessInput(float dt) {
	if (Keys[GLFW_KEY_N]) {
		for (int i = 0; i < ballNum; i++) {
			makeBall(glm::vec2(width / 2 + i, height / 10),
					 glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX),
					 glm::vec2(0));
		}
		// only want one ball per key press
		Keys[GLFW_KEY_N] = false;
	}
	if (Keys[GLFW_KEY_M]) {
		makeBall(glm::vec2(width - 100, height - 200),
				 glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX),
				 glm::vec2(-15, 15));
		// only want one ball per key press
		Keys[GLFW_KEY_M] = false;
	}
	if (MouseButtons[GLFW_MOUSE_BUTTON_RIGHT]) {
		for (int i = 0; i < ballNum; i++) {
			makeBall(glm::vec2(MousePos.x + i, MousePos.y),
					 glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX),
					 glm::vec2(0));
		}
		// only want one ball per press
		MouseButtons[GLFW_MOUSE_BUTTON_RIGHT] = false;
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
	// repeat physics calulations 8 times to add stability
	int subSteps = 8;
	dt = dt / subSteps;
	for (int i = 0; i < subSteps; i++) {
		// if there is a selected ball and the mouse is down, make it follow the mouse pointer
		if (selectedBall && MouseButtons[GLFW_MOUSE_BUTTON_LEFT]) {
			selectedBall->transform->Position += ChangeInMousePos / (float)subSteps;
			// make sure gravity and any other forces don't affect its position
			selectedBall->Physics->ClearVelocity();
		}

		for (GameObject& ball : balls) {
			// if (!(&ball == selectedBall && MouseButtons[GLFW_MOUSE_BUTTON_LEFT]))
			ball.Physics->ResolveForces(dt, {0, -gravity}, damping);
		}
		std::vector<CollisionInfo> collisions = sweepAndPruneCollisions(balls, container);
		//solve collisions
		for (CollisionInfo collision : collisions) {
			collision.A->Physics->ResolveCollision(*collision.B->Physics, collision.points);
		}
	}
}

void Game::Render() {
	if (selectedRenderer == 0) {
		for (GameObject& ball : balls)
			renderer->Draw(*ball.Render);
	}
	if (selectedRenderer == 1) {
		if (triangleCount != (int)circleRenderer->Segments()) {
			delete circleRenderer;
			Shader& ballShader = ResourceManager::GetShader("circle");
			circleRenderer = new CircleRenderer(ballShader, triangleCount);
		}
		for (GameObject& ball : balls)
			circleRenderer->Draw(*ball.Render);
	}
	for (GameObject& c : container) {
		c.Physics->Elasticity = containerElasticity;
		renderer->Draw(*c.Render);
	}
}

void Game::ShowImGuiWindow() {
	ImGui::Begin("Rigid Body Simulator");
	ImGui::Text("%f fps", ImGui::GetIO().Framerate);
	ImGui::Text("Globals:");
	ImGui::Combo("Rendering Method", &selectedRenderer, "texture\0triangle fan\0\0");
	ImGui::SliderInt("Triangle Count", &triangleCount, 1, 32);
	ImGui::SliderFloat("Gravity", &gravity, -25.0f, 50.0f);
	ImGui::SliderFloat("Damping", &damping, 0.0f, 0.9f);
	ImGui::SliderFloat("Container Elasticity", &containerElasticity, 0.0f, 1.0f);
	ImGui::Text("For new balls:");
	ImGui::SliderInt("Number of Balls", &ballNum, 0, 20);
	ImGui::SliderFloat("Radius", &radius, 1.0f, 100.0f);
	ImGui::SliderFloat("Mass", &mass, 1.0f, 100.0f);
	ImGui::SliderFloat("Elasticity", &elasticity, 0.0f, 1.0f);
	if (ImGui::Button("Clear")) {
		selectedBall = nullptr;
		balls.clear();
		ballsIndex.clear();
	}
	ImGui::End();
}

GameObject& Game::makeBall(glm::vec2 center, glm::vec3 color, glm::vec2 velocity) {
	auto ballTex = ResourceManager::GetTexture("ball");
	glm::vec2 pos = center - glm::vec2(radius);

	if (selectedBall) {
		int selectedLoc = 0;
		for (size_t i = 0; i < balls.size(); i++) {
			if (&balls.at(i) == selectedBall) {
				selectedLoc = i;
				selectedBall = nullptr;
			}
		}
		balls.emplace_back(pos, glm::vec2(radius * 2), CIRCLE, ballTex, mass, velocity, color);
		selectedBall = &balls.at(selectedLoc);
	} else
		balls.emplace_back(pos, glm::vec2(radius * 2), CIRCLE, ballTex, mass, velocity, color);
	balls.back().Physics->Elasticity = elasticity;
	ballsIndex.emplace_back(balls.size() - 1);
	return balls.back();
}

std::vector<CollisionInfo> Game::sweepAndPruneCollisions(std::vector<GameObject>& balls, std::vector<GameObject>& container) {
	std::vector<CollisionInfo> collisions;

	std::sort(ballsIndex.begin(), ballsIndex.end(),
			  [&](uint i, uint j) { return (balls[j].transform->Position.x > balls[i].transform->Position.x); });

	for (size_t i = 0; i < ballsIndex.size(); i++) {
		GameObject& ball1 = balls[ballsIndex[i]];
		for (size_t j = i + 1; j < ballsIndex.size(); j++) {
			if (i == j) continue;

			GameObject& ball2 = balls[ballsIndex[j]];
			// if ball2 leftmost x-value > ball1 rightmost x-value, don't check for collision
			if (ball2.transform->Position.x > ball1.transform->Position.x + ball1.transform->Size.x)
				break;
			// otherwise check
			CollisionPoints points = ball1.BoundingVolume->DetectCollision(*ball2.BoundingVolume);
			if (points.HasCollision)
				collisions.emplace_back(&ball1, &ball2, points);
		}
		for (GameObject& c : container) {
			// TODO: improve efficiency of this!
			CollisionPoints points = ball1.BoundingVolume->DetectCollision(*c.BoundingVolume);
			if (points.HasCollision)
				collisions.emplace_back(&ball1, &c, points);
		}
	}
	return collisions;
}
