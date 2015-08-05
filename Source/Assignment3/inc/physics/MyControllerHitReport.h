#ifndef _MY_CONTROLLER_HIT_REPORT_H_
#define	_MY_CONTROLLER_HIT_REPORT_H_

#include "PxPhysicsAPI.h"
#include "characterkinematic\PxController.h"

class MyControllerHitReport : public physx::PxUserControllerHitReport {
public:
	virtual void onShapeHit(const physx::PxControllerShapeHit &hit);

	virtual void onControllerHit(const physx::PxControllersHit &hit){};

	virtual void onObstacleHit(const physx::PxControllerObstacleHit &hit){};
	
	MyControllerHitReport() : PxUserControllerHitReport(){};
	physx::PxVec3 getPlayerContactNormal(){ return _playerContactNormal; };
	void clearPlayercontactNormal(){ _playerContactNormal = physx::PxVec3(0, 0, 0); };
	physx::PxVec3 _playerContactNormal;
};

#endif