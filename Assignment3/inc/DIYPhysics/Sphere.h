#ifndef _SPHERE_H_
#define	_SPHERE_H_

#include "DIYPhysics\RigidBody.h"
#include "glm.hpp"

class Sphere : public RigidBody
{
public:
	Sphere(glm::vec3 _position, glm::vec3 _velocity, float _mass, float _radius, glm::vec4 _colour);
	virtual void Draw();

	float m_radius;

};

#endif