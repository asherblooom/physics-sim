#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glm/glm.hpp>

#include <physics-sim/sprite_renderer.hpp>
#include <physics-sim/texture.hpp>

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject {
public:
	glm::vec3 RenderColor;
	const glm::vec2 RenderSize;
	const Texture2D RenderTexture;

	void Draw(SpriteRenderer& renderer);
	GameObject(glm::vec2 pos, glm::vec2 size, Texture2D texture, glm::vec3 color = glm::vec3(1.0f));

	virtual const glm::vec2& RenderPosition() { return renderPosition; }
	virtual void SetRenderPosition(glm::vec2 position) { this->renderPosition = position; };

protected:
	glm::vec2 renderPosition;
	float rotation;
};

#endif
