#include <physics-sim/game.hpp>

#include <cstdlib>
#include <cstring>

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
	ResourceManager::LoadTexture("ball", "textures/circle.dds");
	ResourceManager::LoadTexture("container", "textures/container.dds");

	glm::vec2 containerPos = glm::vec2(0, 0);
	glm::vec2 containerSize = glm::vec2(width, height);
	container = std::make_unique<PhysObject>(containerPos, containerSize, ResourceManager::GetTexture("container"));
}

void Game::ProcessInput(float dt) {
	if (Keys[GLFW_KEY_N]) {
		makeBall(glm::vec2(960, 100),
				 glm::vec3((float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX, (float)std::rand() / RAND_MAX),
				 glm::vec2(0, 5));
		// only want one ball per key press
		Keys[GLFW_KEY_N] = false;
	}
}

//TODO: make movement fps independent!!!
void Game::Update(float dt) {
	// move balls down
	for (auto& ball : balls) {
		// if ((object->Position + object->Velocity).y >= 1000.0f) continue;
		// object->Position += object->Velocity;
	}
}

void Game::Render() {
	// ObjectManager::RenderObjects(*Renderer);
	for (auto& ball : balls) {
		ball->Draw(*renderer);
	}
	container->Draw(*renderer);
}

PhysObject& Game::makeBall(glm::vec2 pos, glm::vec3 color, glm::vec2 velocity) {
	auto ball = std::make_unique<PhysObject>(pos, glm::vec2(50, 50), ResourceManager::GetTexture("ball"), color, velocity);
	balls.push_back(std::move(ball));
	return *balls.back();
}
