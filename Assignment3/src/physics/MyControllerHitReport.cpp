#include "physics\MyControllerHitReport.h"

void MyControllerHitReport::onShapeHit(const physx::PxControllerShapeHit &hit) {
	physx::PxRigidActor* actor = hit.shape->getActor();
	_playerContactNormal = hit.worldNormal;
	physx::PxRigidDynamic* myActor = actor->is<physx::PxRigidDynamic>();
	if (myActor) {

	}
}