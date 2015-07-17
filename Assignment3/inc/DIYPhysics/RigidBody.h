#ifndef _RIGID_BODY_H_
#define	_RIGID_BODY_H_

#include "DIYPhysics\PhysicsObject.h"
#include "glm.hpp"
#include "glm\ext.hpp"
class RigidBody : public PhysicsObject {
public:
	RigidBody(glm::vec3 _position, glm::vec3 _velocity, glm::quat _rotation, float mass);
	virtual void Update(glm::vec3 _gravity, double _dt);
	virtual void Draw();
	void ApplyForce(glm::vec3 _force);
	void ApplyForceToActor(RigidBody* _actor2, glm::vec3 _force);

	glm::vec3 m_position;
	glm::vec3 m_velocity;
	float m_mass;
	glm::quat m_rotation;
};

#endif