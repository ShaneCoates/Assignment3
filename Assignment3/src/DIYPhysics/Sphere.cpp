#include "DIYPhysics\Sphere.h"
#include "aieutilities\Gizmos.h"
Sphere::Sphere(glm::vec3 _position, glm::vec3 _velocity, float _mass, float _radius, glm::vec4 _colour) : RigidBody(_position, _velocity, glm::quat(), _mass){
	m_colour = _colour;
	m_radius = _radius;
	shapeID = ShapeType::SPHERE;
}

void Sphere::Draw() {
	Gizmos::addSphere(m_position, m_radius, 20, 20, m_colour);
}