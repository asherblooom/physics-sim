#include "game_object.hpp"

GameObject::GameObject(glm::vec2 position, glm::vec2 size, SpriteRenderer& renderer, Texture2D texture, float mass, glm::vec2 velocity, glm::vec3 color)
	: transform{position, size, 1.0f},
	  Render{RenderObject(transform, renderer, texture, color)},
	  Physics{PhysObject(transform, mass, velocity)} {}
