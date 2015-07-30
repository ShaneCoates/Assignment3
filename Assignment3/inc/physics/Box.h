#ifndef _BOX_H_
#define	_BOX_H_
#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <glm.hpp>
#include <aieutilities\Gizmos.h>
using namespace physx;
using namespace glm;
class Box
{
public:
	Box(PxVec3 _transform, PxVec3 _extents, float _density, PxMaterial* _material, PxPhysics* _physics, PxScene* _physicsScene, vec4 _colour = vec4(1), bool _static = false);
	~Box();

	void Update(double _dt);
	void Draw();
private:

	PxRigidActor* m_rigidBody;
	vec3 m_extents;
	vec4 m_colour;
	bool m_static;
};

#endif