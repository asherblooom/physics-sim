#ifndef PHYSOBJECT_HPP
#define PHYSOBJECT_HPP

#include <glm/glm.hpp>

#include <physics-sim/game_object.hpp>
#include <physics-sim/texture.hpp>

class PhysObject;
class Ball;
class Plane;

// TODO: encapsulate this better - in seperate PhysicsEngine class?
struct CollisionPoints {
	glm::vec2 A;	   // Furthest point of A into B
	glm::vec2 B;	   // Furthest point of B into A
	glm::vec2 Normal;  // B – A normalized
	float Depth;	   // Length of B – A
	bool HasCollision;
};
struct CollisionInfo {
	PhysObject* A;
	PhysObject* B;
	CollisionPoints points;
};

// a general object that can be manipulated by the physics engine
class PhysObject : public GameObject {
   public:
	glm::vec2 Center;
	const float Mass;

	PhysObject(glm::vec2 center, glm::vec2 size, float mass, Texture2D texture, glm::vec3 color = glm::vec3(1.0f),
			   glm::vec2 velocity = glm::vec2(0.0f));

	void AddForce(glm::vec2 force) {
		this->force.x += force.x;
		// down is +ve y, up is moving towards y=0 (so -ve y)
		this->force.y += -force.y;
	}
	// will update center based on forces added
	void ResolveForces(float dt);
	void ClearForces() { force = glm::vec3(0); }
	void ClearVelocity() { velocity = glm::vec3(0); }

	// collision functions using visitor pattern/double dispatch
	virtual CollisionPoints DetectCollision(PhysObject& obj) = 0;
	virtual CollisionPoints CollideWithBall(Ball& b) = 0;
	virtual CollisionPoints CollideWithPlane(Plane& p) = 0;

	// need to calculate position from center when getting and vice versa when setting
	// done this way as position (used for rendering) will most likely be queried far less than center (used for physics)
	void SetRenderPosition(glm::vec2 position) override;
	const glm::vec2& RenderPosition() override;

   protected:
	glm::vec2 velocity, force;
};

// a ball object
class Ball : public PhysObject {
   public:
	const float Radius;
	Ball(glm::vec2 center, float diameter = 1.0f, float mass = 1.0f, glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f));

	CollisionPoints DetectCollision(PhysObject& obj) override {
		return obj.CollideWithBall(*this);
	}
	CollisionPoints CollideWithBall(Ball& b) override;
	CollisionPoints CollideWithPlane(Plane& p) override;
};

// a plane object
class Plane : public PhysObject {
   public:
	const glm::vec2 Normal;
	float Distance = 0;	 //??
	float Length;
	Plane(glm::vec2 center, glm::vec2 normal, float length, glm::vec3 color = glm::vec3(1.0f));

	CollisionPoints DetectCollision(PhysObject& obj) override {
		return obj.CollideWithPlane(*this);
	}
	CollisionPoints CollideWithBall(Ball& b) override;
	CollisionPoints CollideWithPlane(Plane& p) override;
};

#endif
