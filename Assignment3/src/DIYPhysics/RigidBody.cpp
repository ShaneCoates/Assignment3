#include "DIYPhysics\RigidBody.h"

RigidBody::RigidBody(glm::vec3 _position, glm::vec3 _velocity, glm::quat _rotation, float mass) {

	m_position = _position;
	m_velocity = _velocity;
	m_mass = m_mass;
	m_rotation = _rotation;
}
void RigidBody::ApplyForce(glm::vec3 _force) {

}
void RigidBody::ApplyForceToActor(RigidBody* _actor2, glm::vec3 _force) {

}