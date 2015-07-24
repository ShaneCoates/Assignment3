#include "DIYPhysics\RigidBody.h"

RigidBody::RigidBody(glm::vec3 _position, glm::vec3 _velocity, glm::quat _rotation, float _mass) {

	m_position = _position;
	m_velocity = _velocity;
	m_mass = _mass;
	m_rotation = _rotation;
	m_static = false;
}
void RigidBody::ApplyForce(glm::vec3 _force) {
	m_velocity += _force / m_mass;
}
void RigidBody::ApplyForceToActor(RigidBody* _actor2, glm::vec3 _force) {

}
void RigidBody::Update(glm::vec3 _gravity, double _dt) {
	if (!m_static) {
		m_velocity += _gravity;
		m_velocity.x *= 0.99f;
		m_velocity.y *= 0.99f;
		m_velocity.z *= 0.99f;

		m_position += m_velocity * _dt;
	}
}
void RigidBody::Draw(){

}
