#include "physics\Ball.h"
#include "Utils.h"
Ball::Ball(PxVec3 _transform, PxReal _radius, float _density, PxMaterial* _material, PxPhysics* _physics, PxScene* _physicsScene, vec4 _colour) {
	m_colour = _colour;
	m_radius = _radius;
	m_rigidBody = PxCreateDynamic(*_physics, PxTransform(_transform), PxSphereGeometry(_radius), *_material, _density);
	_physicsScene->addActor(*m_rigidBody);
}

Ball::~Ball() {

}

void Ball::Update(double _dt) {

}

void Ball::Draw(){
	vec3 center;
	Utils::ConvertVec3(m_rigidBody->getWorldBounds().getCenter(), center);
	glm::mat4 newRot = Utils::TransformToMat4(m_rigidBody->getGlobalPose());
	Gizmos::addSphere(center, m_radius, 25, 25, m_colour, &newRot);
}