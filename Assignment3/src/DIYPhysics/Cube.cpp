#include "DIYPhysics\Cube.h"
#include "aieutilities\Gizmos.h"
Cube::Cube(glm::vec3 _position, glm::vec3 _extents, glm::vec3 _velocity, float _mass, glm::vec4 _colour) : RigidBody(_position, _velocity, glm::quat(), _mass) {
	m_colour = _colour;
	m_extents = _extents;
	shapeID = ShapeType::BOX;
}

void Cube::Draw() {
	Gizmos::addAABB(m_position, m_extents, m_colour);
}