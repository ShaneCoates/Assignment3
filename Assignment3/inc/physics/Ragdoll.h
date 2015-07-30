#ifndef _RAGDOLL_H_
#define	_RAGDOLL_H_
#include <PxPhysicsAPI.h>
#include <PxScene.h>
using namespace physx;

enum RagdollParts {
	NO_PARENT = -1,
	LOWER_SPINE,
	LEFT_PELVIS,
	RIGHT_PELVIS,
	LEFT_UPPER_LEG,
	RIGHT_UPPER_LEG,
	LEFT_LOWER_LEG,
	RIGHT_LOWER_LEG,
	UPPER_SPINE,
	LEFT_CLAVICLE,
	RIGHT_CLAVICLE,
	NECK,
	HEAD,
	LEFT_UPPER_ARM,
	RIGHT_UPPER_ARM,
	LEFT_LOWER_ARM,
	RIGHT_LOWER_ARM,
};

const PxVec3 X_AXIS = PxVec3(1, 0, 0);
const PxVec3 Y_AXIS = PxVec3(0, 1, 0);
const PxVec3 Z_AXIS = PxVec3(0, 0, 1);

struct RagdollNode {
	PxQuat globalRotation;
	PxVec3 scaleGlobalPos;
	int parentNodeID;
	float halfLength;
	float radius;
	float parentLinkPos;
	float childLinkPos;
	char* name;
	PxArticulationLink* linkPtr;
	RagdollNode(PxQuat _globalRotation, int _parentNodeID, float _halfLength, float _radius, float _parentLinkPos, float _childLinkPos, char* _name) {
		globalRotation = _globalRotation;
		parentNodeID = _parentNodeID;
		halfLength = _halfLength;
		radius = _radius;
		parentLinkPos = _parentLinkPos;
		childLinkPos = _childLinkPos;
		name = _name;
		linkPtr = nullptr;
	}
};

class Ragdoll {
public:
	Ragdoll(PxPhysics* _physics, PxScene* _scene, PxMaterial* _ragdollMaterial);
	~Ragdoll();

	void Update(double _dt);
	void Draw();

	PxArticulation* MakeRagdoll(PxPhysics* _physics, RagdollNode** _nodeArray, PxTransform _worldPos, float _scaleFactor, PxMaterial* _ragdollMaterial);
	void AddForce(PxVec3 _direction);

	void WakeUp();
private:
	PxArticulation* m_ragdoll;
	PxScene* m_scene;

};

#endif