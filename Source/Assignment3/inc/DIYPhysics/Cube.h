#ifndef _CUBE_H_
#define	_CUBE_H_

#include "DIYPhysics\RigidBody.h"
#include "glm.hpp"

class Cube : public RigidBody
{
public:
	Cube(glm::vec3 _position, glm::vec3 _extents, glm::vec3 _velocity, float _mass, glm::vec4 _colour);
	virtual void Draw();

	glm::vec3 m_extents;
	glm::vec4 m_colour;
};

#endif