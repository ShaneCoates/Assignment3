#ifndef _SPRING_H_
#define	_SPRING_H_

#include "DIYPhysics\PhysicsObject.h"
#include "DIYPhysics\RigidBody.h"

#include "glm.hpp"
class Spring : public PhysicsObject {
public:
	Spring(RigidBody* _object1, RigidBody* _object2, float _springCoefficient = 1, float _distance = 0);

	virtual void Update(glm::vec3 _gravity, double _dt);
	virtual void Draw();

	RigidBody* m_object1;
	RigidBody* m_object2;

	float m_springCoefficient;
	float m_distance;
};

#endif