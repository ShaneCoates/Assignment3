#include "Utils.h"

glm::mat4 Utils::TransformToMat4(PxTransform _transform) {
	return(mat4_cast(quat(_transform.q.w, _transform.q.x, _transform.q.y, _transform.q.z)));
}
void Utils::ConvertVec3(PxVec3 _in, vec3& _out) {
	_out = vec3(_in.x, _in.y, _in.z);
}
void Utils::ConvertVec3(vec3 _in, PxVec3& _out) {
	_out = PxVec3(_in.x, _in.y, _in.z);
}