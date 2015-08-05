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
void Utils::AddWidget(PxShape* _shape, PxRigidActor* _actor, glm::vec4 _colour) {
	PxGeometryType::Enum type = _shape->getGeometryType();
	
	switch (type)
	{
	case PxGeometryType::eBOX:
		AddBox(_shape, _actor, _colour);
		break;
	case PxGeometryType::eSPHERE:
		AddSphere(_shape, _actor, _colour);
		break;
	case PxGeometryType::eCAPSULE:
		AddCapsule(_shape, _actor, _colour);
		break;
	default:
		AddSphere(_shape, _actor, _colour);
		break;
	}
}
void Utils::AddBox(PxShape* _shape, PxRigidActor* _actor, glm::vec4 _colour) {
	vec3 BoxCenter, BoxExtents;
	PxBoxGeometry geometry;
	_shape->getBoxGeometry(geometry);
	Utils::ConvertVec3(_actor->getWorldBounds().getCenter(), BoxCenter);
	Utils::ConvertVec3(geometry.halfExtents, BoxExtents);

	glm::mat4 newRot = Utils::TransformToMat4(_actor->getGlobalPose());
	Gizmos::addAABBFilled(BoxCenter, BoxExtents, _colour, &newRot);
}
void Utils::AddSphere(PxShape* _shape, PxRigidActor* _actor, glm::vec4 _colour) {
	vec3 center;
	PxSphereGeometry geometry;
	_shape->getSphereGeometry(geometry);
	float radius = geometry.radius;
	Utils::ConvertVec3(_actor->getWorldBounds().getCenter(), center);
	glm::mat4 newRot = Utils::TransformToMat4(_actor->getGlobalPose());
	Gizmos::addSphere(center, radius, 5, 5, _colour, &newRot);
}
void Utils::AddCapsule(PxShape* _shape, PxRigidActor* _actor, glm::vec4 _colour) {
	vec3 center;
	PxCapsuleGeometry geometry;
	_shape->getCapsuleGeometry(geometry);
	float radius = geometry.radius;
	float halfHeight = geometry.halfHeight;
	Utils::ConvertVec3(_actor->getWorldBounds().getCenter(), center);
	glm::mat4 newRot = Utils::TransformToMat4(_actor->getGlobalPose());
	PxTransform transform = PxShapeExt::getGlobalPose(*_shape, *_actor);
	PxMat44 m(transform); //Create a rotation matrix from transform
	glm::mat4* M = (glm::mat4*)(&m);
	//get the world position from the PhysX tranform
	Utils::ConvertVec3(transform.p, center);
	glm::vec4 axis(halfHeight, 0, 0, 0); //axis for the capsule
	axis = *M * axis; //rotate axis to correct orientation
	//add our 2 end cap spheres...
	Gizmos::addSphere(center + axis.xyz(), radius, 10, 10, glm::vec4(1));
	Gizmos::addSphere(center - axis.xyz(), radius, 10, 10, glm::vec4(1));
	//Fix the gizmo rotation
	glm::mat4 m2 = glm::rotate(*M, 11 / 7.0f, glm::vec3(0.0f, 0.0f, 1.0f));


	Gizmos::addCylinderFilled(center, radius, halfHeight, 10, _colour, &m2);

}