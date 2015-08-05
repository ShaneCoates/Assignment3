#include "DIYPhysics\Plane.h"
#include "aieutilities\Gizmos.h"
Plane::Plane(glm::vec3 _normal, float _distanceFromOrigin) {
	m_normal = _normal;
	m_distanceFromOrigin = _distanceFromOrigin;
	shapeID = ShapeType::PLANE;
}

void Plane::Update(glm::vec3 _gravity, double _dt) {

}
void Plane::Draw() {
	glm::vec3 pos = m_normal * m_distanceFromOrigin;
	Gizmos::addAABBFilled(pos, glm::vec3(100, 0.01f, 100), glm::vec4(0, 1, 0, 1));
}

