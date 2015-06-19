#ifndef _BALL_H_
#define	_BALL_H_
#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <glm.hpp>
#include <aieutilities\Gizmos.h>
using namespace physx;
using namespace glm;
class Ball
{
public:
	Ball(PxVec3 _transform, PxReal _radius, float _density, PxMaterial* _material, PxPhysics* _physics, PxScene* _physicsScene, vec4 _colour = vec4(1));
	~Ball();

	void Update(double _dt);
	void Draw();
private:

	PxRigidDynamic* m_rigidBody;
	PxReal m_radius;
	vec4 m_colour;
};

#endif