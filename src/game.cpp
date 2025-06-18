#include <physics-sim/ball.hpp>
#include <physics-sim/game.hpp>
#include <physics-sim/phys_object.hpp>
#include "physics-sim/object_manager.hpp"

SpriteRenderer* spriteRenderer;

Game::Game(unsigned int width, unsigned int height)
	: Width(width), Height(height), Keys() {
}

Game::~Game() {
}

void Game::Init() {
	// load shaders
	ResourceManager::LoadShader("sprite", "src/shaders/sprite.vs", "src/shaders/sprite.frag");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, (float)(this->Width), (float)(this->Height), 0.0f, -1.0f, 1.0f);
	Shader spriteShader = ResourceManager::GetShader("sprite");
	spriteShader.Use();
	spriteShader.SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);
	// set render-specific controls
	spriteRenderer = new SpriteRenderer(spriteShader);
	// load textures
	ResourceManager::LoadTexture("ball", "textures/awesomeface.dds", true);
}

void Game::ProcessInput(float dt) {
	if (Keys[GLFW_KEY_N]) {
		// add ball
		ObjectManager::addObject<Ball>("ball1", glm::vec2(960, 100), glm::vec3(1, 1, 1), glm::vec2(0, 10));
	}
}

void Game::Update(float dt) {
}

void Game::Render() {
	ObjectManager::renderObjects(*spriteRenderer);
}
