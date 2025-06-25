#include <physics-sim/game.hpp>

#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

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
	ResourceManager::LoadTexture("container", "textures/container.dds");

	glm::vec2 containerPos = glm::vec2(0, 0);
	glm::vec2 containerSize = glm::vec2(width, height);
	container = std::make_unique<PhysObject>(containerPos, containerSize, ResourceManager::GetTexture("container"));
}

void Game::ProcessInput(float dt) {
	if (Keys[GLFW_KEY_N]) {
		makeBall(glm::vec2(width / 2, height / 10),
				 glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX),
				 glm::vec2(0, 5));
		// only want one ball per key press
		Keys[GLFW_KEY_N] = false;
	}
	// if no ball currently selected and left mouse button down, select a ball which is over the mouse pointer
	if (MouseButtons[GLFW_MOUSE_BUTTON_LEFT] && !selectedBall.first) {
		// loop through balls in reverse order, so as to pick the one on top (drawn last) if any overlap
		for (int i = balls.size() - 1; i >= 0; i--) {
			Ball& ball = balls[i];
			auto distance = std::sqrt(std::pow(MousePos.x - ball.Center().x, 2) + std::pow(MousePos.y - ball.Center().y, 2));
			if (distance <= ball.Size.x / 2.0f) {
				selectedBall = {&ball, ball.Color};
				// set selected ball to white
				ball.Color = glm::vec3(1);
				// only select one ball
				break;
			}
		}
		// reset selected ball to old colour
	} else if (!MouseButtons[GLFW_MOUSE_BUTTON_LEFT] && selectedBall.first) {
		selectedBall.first->Color = selectedBall.second;
		selectedBall.first = nullptr;
	}
}

//TODO: make movement fps independent!!!
void Game::Update(float dt) {
	// if there is a selected ball, make it follow the mouse pointer
	if (selectedBall.first) {
		selectedBall.first->SetCenter(selectedBall.first->Center() + ChangeInMousePos);
	}

	// move balls down
	for (auto& ball : balls) {
		// if ((object->Position + object->Velocity).y >= 1000.0f) continue;
		// object->Position += object->Velocity;
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
	auto ball = Ball(pos, 1.0f, color, velocity);
	balls.push_back(std::move(ball));
	return balls.back();
}
