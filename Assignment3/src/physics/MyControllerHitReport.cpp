#include "physics\MyControllerHitReport.h"

void MyControllerHitReport::onShapeHit(const physx::PxControllerShapeHit &hit) {
	physx::PxRigidActor* actor = hit.shape->getActor();
	_playerContactNormal = hit.worldNormal;
	physx::PxRigidDynamic* myActor = actor->is<physx::PxRigidDynamic>();
	if (myActor) {
		myActor->addForce(hit.dir);
	}
	physx::PxArticulation* myRagdoll = actor->is<physx::PxArticulation>();
	if (myRagdoll) {
		physx::PxU32 nLinks = myRagdoll->getNbLinks();
		physx::PxArticulationLink** links = new physx::PxArticulationLink*[nLinks];
		myRagdoll->getLinks(links, nLinks);
		while (nLinks--) {
			links[nLinks]->addForce(hit.dir);
		}

	}
}