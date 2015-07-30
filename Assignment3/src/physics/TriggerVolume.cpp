#include "physics\TriggerVolume.h"
#include "Utils.h"
#include "aieutilities\Gizmos.h"
using namespace physx;
TriggerVolume::TriggerVolume(PxScene* _scene, PxRigidStatic* _actor, PxShape* _shape) {
	m_actor = _actor;
	m_shape = _shape;
	m_shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	m_shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	m_actor->attachShape(*_shape);
	_scene->setSimulationEventCallback(this);
	m_triggered = false;
}
TriggerVolume::~TriggerVolume() {

}
void TriggerVolume::Update(double _dt) {
	m_triggered = false;
}
void TriggerVolume::Draw() {
	Utils::AddWidget(m_shape, m_actor, glm::vec4(0));
}
void TriggerVolume::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs) {
	m_triggered = true;
}
void TriggerVolume::onTrigger(PxTriggerPair* pairs, PxU32 count) {
	m_triggered = true;
}