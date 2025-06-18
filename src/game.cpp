#include <physics-sim/game.hpp>
#include <physics-sim/phys_object.hpp>

SpriteRenderer *spriteRenderer;

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
	ResourceManager::LoadTexture("face", "textures/results.dds", true);
}

void Game::ProcessInput(float dt) {
	if (Keys[GLFW_KEY_N]) {
		// add ball
		PhysObject ball = new PhysObject(startingPos, ballSize, balltex, randomColor, startingVelocity);
	}
}

void Game::Update(float dt) {
}

void Game::Render() {
	Texture2D face = ResourceManager::GetTexture("face");
	spriteRenderer->DrawSprite(face, glm::vec2(500.0f, 500.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
