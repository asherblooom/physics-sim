#include <physics-sim/game.hpp>

#include <cstdlib>
#include <cstring>
#include <memory>

Game::Game(unsigned int width, unsigned int height)
	: width(width), height(height), Keys() {
}

void Game::Init() {
	// load shaders
	ResourceManager::LoadShader("sprite", "src/shaders/sprite.vs", "src/shaders/sprite.frag");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, (float)(this->width), (float)(this->height), 0.0f, -1.0f, 1.0f);
	Shader& spriteShader = ResourceManager::GetShader("sprite");
	spriteShader.Use();
	spriteShader.SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);
	// set render-specific controls
	renderer = new SpriteRenderer(spriteShader);
	// load textures
	ResourceManager::LoadTexture("ball", "textures/awesomeface.dds");
}

void Game::ProcessInput(float dt) {
	if (Keys[GLFW_KEY_N]) {
		// auto ball1 = ObjectManager::addObject<Ball>(glm::vec2(960, 100),
		// 											glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX),
		// 											glm::vec2(0, 5));
		addObject<Ball>(glm::vec2(960, 100),
						glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX),
						glm::vec2(0, 5));

		// only want one ball per key press
		Keys[GLFW_KEY_N] = false;
	}
}

//TODO: make movement fps independent!!!
void Game::Update(float dt) {
	// move balls down
	for (auto& object : objects) {
		if (std::strcmp(typeid(object).name(), "Ball")) {
			// if ((object->Position + object->Velocity).y >= 1000.0f) continue;
			// object->Position += object->Velocity;
		}
	}
}

void Game::Render() {
	// ObjectManager::RenderObjects(*Renderer);
	for (auto& object : objects) {
		object->Draw(*renderer);
	}
}
