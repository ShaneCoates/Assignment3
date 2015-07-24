#include "DIYPhysics\Spring.h"
#include "aieutilities\Gizmos.h"
Spring::Spring(RigidBody* _object1, RigidBody* _object2, float _springCoefficient) : PhysicsObject(){
	m_object1 = _object1;
	m_object2 = _object2;
	m_springCoefficient = _springCoefficient;
}

void Spring::Update(glm::vec3 _gravity, double _dt) {
	
	glm::vec3 direction = m_object1->m_position - m_object2->m_position;
	direction *= -m_springCoefficient;
	m_object1->ApplyForce(direction);
	m_object2->ApplyForce(-direction);
}

void Spring::Draw() {
	Gizmos::addLine(m_object1->m_position, m_object2->m_position, glm::vec4(1, 1, 1, 1));
}