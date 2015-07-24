#ifndef _PHYSICS_SCENE_H_
#define	_PHYSICS_SCENE_H_

#include <vector>
#include "DIYPhysics\PhysicsObject.h"

class PhysicsScene {
public:

	void AddActor(PhysicsObject* _actor);
	void RemoveActor(PhysicsObject* _actor);
	void Update(double _dt);
	void Draw();

	bool SphereToSphere(PhysicsObject* _actor1, PhysicsObject* _actor2);
	bool SphereToPlane(PhysicsObject* _actor1, PhysicsObject* _actor2);
	bool SphereToCube(PhysicsObject* _actor1, PhysicsObject* _actor2);

	glm::vec3 m_gravity;
	float m_timeStep;
	std::vector<PhysicsObject*> m_actors;
};

#endif