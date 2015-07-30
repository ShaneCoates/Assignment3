#ifndef _UTILS_H_
#define	_UTILS_H_
#include <PxPhysicsAPI.h>
#include <glm.hpp>
#include <ext.hpp>
#include "aieutilities\Gizmos.h"
using namespace glm;
using namespace physx;
class Utils
{
public:
	static mat4 TransformToMat4(PxTransform _transform);
	static void ConvertVec3(PxVec3 _in, vec3& _out);
	static void ConvertVec3(vec3 _in, PxVec3& _out);
	static void AddWidget(PxShape* _shape, PxRigidActor* _actor, glm::vec4 _colour = glm::vec4(1));
	static void AddBox(PxShape* _shape, PxRigidActor* _actor, glm::vec4 _colour = glm::vec4(1));
	static void AddSphere(PxShape* _shape, PxRigidActor* _actor, glm::vec4 _colour = glm::vec4(1));
	static void AddCapsule(PxShape* _shape, PxRigidActor* _actor, glm::vec4 _colour = glm::vec4(1));
private:

};


#endif