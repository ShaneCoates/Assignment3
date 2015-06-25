#ifndef _PHYSICS_OBJECT_H_
#define	_PHYSICS_OBJECT_H_

#include "glm.hpp"

enum ShapeType{
	PLANE = 0,
	SPHERE = 1,
	BOX = 2
}

class PhysicsObject {
public:
	ShapeType shapeID;
	void virtual Update(glm::vec3 _gravity, double _dt) = 0;
	void virtual Debug() = 0;
	void virtual MakeGizmo() = 0;
	void virtual ResetPosition(){};
};

#endif