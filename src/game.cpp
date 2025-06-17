#include <physics-sim/game.hpp>

SpriteRenderer *Renderer;

Game::Game(unsigned int width, unsigned int height)
	: Width(width), Height(height), Keys() {
}

Game::~Game() {
}

void Game::Init() {
	// load shaders
	ResourceManager::LoadShader("src/shaders/sprite.vs", "src/shaders/sprite.frag", nullptr, "sprite");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	Shader spriteShader = ResourceManager::GetShader("sprite");
	spriteShader.Use();
	spriteShader.SetInteger("image", 0);
	spriteShader.SetMatrix4("projection", projection);
	// set render-specific controls
	Renderer = new SpriteRenderer(spriteShader);
	// load textures
	ResourceManager::LoadTexture("face", "textures/awesomeface.dds", true);
}

void Game::Update(float dt) {
}

void Game::ProcessInput(float dt) {
}

void Game::Render() {
	Texture2D face = ResourceManager::GetTexture("face");
	Renderer->DrawSprite(face, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
