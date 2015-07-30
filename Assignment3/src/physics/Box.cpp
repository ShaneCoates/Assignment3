#include "physics\Box.h"
#include "Utils.h"
Box::Box(PxVec3 _transform, PxVec3 _extents, float _density, PxMaterial* _material, PxPhysics* _physics, PxScene* _physicsScene, vec4 _colour, bool _static) {
	m_colour = _colour;
	Utils::ConvertVec3(_extents, m_extents);
	if (!_static) {
		m_rigidBody = PxCreateDynamic(*_physics, PxTransform(_transform), PxBoxGeometry(_extents), *_material, _density);
	}
	else {
		m_rigidBody = PxCreateStatic(*_physics, PxTransform(_transform), PxBoxGeometry(_extents), *_material);
	}
	_physicsScene->addActor(*m_rigidBody);
}

Box::~Box() {

}

void Box::Update(double _dt) {

}

void Box::Draw(){
	vec3 BoxCenter;
	Utils::ConvertVec3(m_rigidBody->getWorldBounds().getCenter(), BoxCenter);
	glm::mat4 newRot = Utils::TransformToMat4(m_rigidBody->getGlobalPose());
	Gizmos::addAABBFilled(BoxCenter, m_extents, m_colour, &newRot);
}