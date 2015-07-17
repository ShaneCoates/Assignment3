#ifndef _PLANE_H_
#define	_PLANE_H_

#include "DIYPhysics\PhysicsObject.h"
#include "glm.hpp"
class Plane : public PhysicsObject {
public:
	Plane(glm::vec3 _normal, float _distanceFromOrigin);

	virtual void Update(glm::vec3 _gravity, double _dt);
	virtual void Draw();

	glm::vec3 m_normal;
	float m_distanceFromOrigin;
};

#endif