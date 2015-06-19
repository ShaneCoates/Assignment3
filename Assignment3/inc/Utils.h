#ifndef _UTILS_H_
#define	_UTILS_H_
#include <PxPhysicsAPI.h>
#include <glm.hpp>
#include <ext.hpp>
using namespace glm;
using namespace physx;
class Utils
{
public:
	static mat4 TransformToMat4(PxTransform _transform);
	static void ConvertVec3(PxVec3 _in, vec3& _out);
	static void ConvertVec3(vec3 _in, PxVec3& _out);

private:

};


#endif