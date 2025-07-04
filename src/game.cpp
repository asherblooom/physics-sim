#include <physics-sim/game.hpp>

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <physics-sim/plane.hpp>

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

	container = std::make_unique<Plane>(glm::vec2(width / 2, height - 20), glm::vec2(0, 1), width);
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
	// if no ball currently selected and left mouse button down, select a ball which is over the mouse pointer
	// loop through balls in reverse order, so as to pick the one on top (drawn last) if any overlap
	if (selectedBall && !MouseButtons[GLFW_MOUSE_BUTTON_LEFT]) {
		auto selctedDistance = std::sqrt(std::pow(MousePos.x - selectedBall->Center.x, 2) + std::pow(MousePos.y - selectedBall->Center.y, 2));
		if (selctedDistance > selectedBall->RenderSize.x / 2.0f) {
			selectedBall->RenderColor -= glm::vec3(0.1);
			selectedBall = nullptr;
		}
	}
	if (!selectedBall) {
		for (int i = balls.size() - 1; i >= 0; i--) {
			Ball& ball = balls[i];
			auto distance = std::sqrt(std::pow(MousePos.x - ball.Center.x, 2) + std::pow(MousePos.y - ball.Center.y, 2));
			if (distance <= ball.RenderSize.x / 2.0f) {
				selectedBall = &ball;
				// make selected ball brighter
				ball.RenderColor += glm::vec3(0.1);
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
		selectedBall->Center = selectedBall->Center + ChangeInMousePos;
		selectedBall->ClearVelocity();
	}

	// move balls down
	for (auto& ball : balls) {
		if (&ball == selectedBall && MouseButtons[GLFW_MOUSE_BUTTON_LEFT]) continue;
		ball.AddForce(gravity * ball.Mass);
		ball.ResolveForces(dt);
		ball.ClearForces();
	}
}

void Game::Render() {
	// ObjectManager::RenderObjects(*Renderer);
	for (auto& ball : balls) {
		ball.Draw(*renderer);
	}
	container->Draw(*renderer);
}

PhysObject& Game::makeBall(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity) {
	auto ball = Ball(pos, 1.0f, 1.0f, color, velocity);
	balls.push_back(std::move(ball));
	return balls.back();
}
