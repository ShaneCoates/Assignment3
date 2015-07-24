#include "DIYPhysics\PhysicsScene.h"
#include "DIYPhysics\Sphere.h"
#include "DIYPhysics\Plane.h"
#include "DIYPhysics\Cube.h"

void PhysicsScene::AddActor(PhysicsObject* _actor) {
	bool exists = false;
	for each (PhysicsObject* obj in m_actors)
	{
		if (obj == _actor) {
			exists = true;
			return;
		}
	}
	if (exists == false) {
		m_actors.push_back(_actor);
	}
}

void PhysicsScene::RemoveActor(PhysicsObject* _actor) {
	for (auto i = m_actors.begin(); i != m_actors.end(); i++) {
		m_actors.erase(i);
	}
}

void PhysicsScene::Update(double _dt) {
	for (auto it = m_actors.begin(); it != m_actors.end(); ++it)
	{
		(*it)->Update(m_gravity, _dt);

		if ((*it)->shapeID == ShapeType::SPHERE)
		{
			for (auto it2 = m_actors.begin(); it2 != m_actors.end(); ++it2)
			{
				if ((*it) != (*it2)) {
					if ((*it2)->shapeID == ShapeType::PLANE)
					{
						SphereToPlane((*it), (*it2));
					}
					if ((*it2)->shapeID == ShapeType::SPHERE)
					{
						SphereToSphere((*it), (*it2));
					}
					if ((*it2)->shapeID == ShapeType::BOX)
					{
						SphereToCube((*it), (*it2));
					}
				}
			}
		}
	}
}

void PhysicsScene::Draw() {
	for each (PhysicsObject* obj in m_actors)
	{
		obj->Draw();
	}
}

bool PhysicsScene::SphereToSphere(PhysicsObject* _actor1, PhysicsObject* _actor2) {
	Sphere* sphere1 = dynamic_cast<Sphere*>(_actor1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(_actor2);

	if (sphere1 != nullptr && sphere2 != nullptr) {
		float dist = glm::distance(sphere1->m_position, sphere2->m_position);
		float intersect = sphere1->m_radius + sphere2->m_radius - dist;

		if (intersect > 0) {
			glm::vec3 delta = sphere1->m_position - sphere2->m_position;
			glm::vec3 collisionNormal = glm::normalize(delta);
			glm::vec3 relativeVelocity = sphere1->m_velocity - sphere2->m_velocity;
			glm::vec3 collisionVector = collisionNormal * (glm::dot(relativeVelocity, collisionNormal));
			glm::vec3 forceVector = collisionVector * 1.0f / (1 / sphere1->m_mass + 1 / sphere2->m_mass);

			sphere1->ApplyForce(2.0f * -forceVector);
			sphere2->ApplyForce(2.0f * forceVector);

			float totalMass = sphere1->m_mass + sphere2->m_mass;

			glm::vec3 seperationVector = collisionNormal * intersect;
			sphere1->m_position += (seperationVector * (sphere2->m_mass / totalMass));
			sphere2->m_position -= (seperationVector * (sphere1->m_mass / totalMass));
			
			return true;
		}
	}
	return false;
}

bool PhysicsScene::SphereToPlane(PhysicsObject* _actor1, PhysicsObject* _actor2) {
	Sphere* sphere = dynamic_cast<Sphere*>(_actor1);
	Plane* plane = dynamic_cast<Plane*>(_actor2);

	if (sphere != nullptr && plane != nullptr) {
		glm::vec3 collisionNormal = plane->m_normal;
		float sphereToPlane = glm::dot(sphere->m_position, plane->m_normal) - plane->m_distanceFromOrigin;


		float intersection = sphere->m_radius - sphereToPlane;

		if (intersection > 0) {
			glm::vec3 relativeVelocity = sphere->m_velocity;
			glm::vec3 planeNormal = collisionNormal;
			glm::vec3 forceVector = -1 * sphere->m_mass * planeNormal * (glm::dot(planeNormal, sphere->m_velocity));

			sphere->ApplyForce(forceVector * glm::vec3(2));
			sphere->m_position += collisionNormal * intersection;

			return true;
		}
	}
	return false;
}
inline float squared(float v) { return v * v; }
bool PhysicsScene::SphereToCube(PhysicsObject* _actor1, PhysicsObject* _actor2) {
	Sphere* sphere = dynamic_cast<Sphere*>(_actor1);
	Cube* cube = dynamic_cast<Cube*>(_actor2);

	float halfCubeX = cube->m_extents.x;
	float halfCubeY = cube->m_extents.y;
	float halfCubeZ = cube->m_extents.z;

	glm::vec3 TopBackLeft = cube->m_position - glm::vec3(halfCubeX, halfCubeY, -halfCubeZ);
	glm::vec3 TopBackRight = cube->m_position - glm::vec3(-halfCubeX, halfCubeY, -halfCubeZ);
	glm::vec3 TopFrontLeft = cube->m_position - glm::vec3(halfCubeX, halfCubeY, halfCubeZ);
	glm::vec3 TopFrontRight = cube->m_position - glm::vec3(-halfCubeX, halfCubeY, halfCubeZ);

	glm::vec3 BottomBackLeft = cube->m_position - glm::vec3(halfCubeX, -halfCubeY, -halfCubeZ);
	glm::vec3 BottomBackRight = cube->m_position - glm::vec3(-halfCubeX, -halfCubeY, -halfCubeZ);
	glm::vec3 BottomFrontLeft = cube->m_position - glm::vec3(halfCubeX, -halfCubeY, halfCubeZ);
	glm::vec3 BottomFrontRight = cube->m_position - glm::vec3(-halfCubeX, -halfCubeY, halfCubeZ);

	float fIntersectDist;
	glm::vec3 collisionNormal;
	float fXSmallestOverlap = 10000000;
	float fYSmallestOverlap = 10000000;
	float fZSmallestOverlap = 10000000;
	float fSmallestOverlap = 10000000;

	float fCubeMinX = BottomFrontLeft.x;
	float fCubeMaxX = BottomFrontRight.x;

	float fSphereMinX = sphere->m_position.x - sphere->m_radius;
	float fSphereMaxX = sphere->m_position.x + sphere->m_radius;

	float fCubeMinY = TopFrontLeft.y;
	float fCubeMaxY = BottomBackRight.y;

	float fSphereMinY = sphere->m_position.y - sphere->m_radius;
	float fSphereMaxY = sphere->m_position.y + sphere->m_radius;

	float fCubeMinZ = BottomFrontLeft.z;
	float fCubeMaxZ = BottomBackRight.z;

	float fSphereMinZ = sphere->m_position.z - sphere->m_radius;
	float fSphereMaxZ = sphere->m_position.z + sphere->m_radius;


	if (fCubeMaxX > fSphereMinX && fSphereMaxX > fCubeMinX) {
		float fXOverlap1 = fCubeMaxX - fSphereMinX;
		float fXOverlap2 = fCubeMinX - fSphereMaxX;

		if (glm::abs(fXOverlap1) < glm::abs(fXOverlap2)) {
			fXSmallestOverlap = fXOverlap1;
		}
		else {
			fXSmallestOverlap = fXOverlap2;
		}
		collisionNormal = glm::vec3(1, 0, 0);
		fIntersectDist = fXSmallestOverlap;
		fSmallestOverlap = fXSmallestOverlap;
	}
	else {
		return false;
	}
	if (fCubeMaxY > fSphereMinY && fSphereMaxY > fCubeMinY) {
		float fYOverlap1 = fCubeMaxY - fSphereMinY;
		float fYOverlap2 = fCubeMinY - fSphereMaxY;

		if (glm::abs(fYOverlap1) < glm::abs(fYOverlap2)) {
			fYSmallestOverlap = fYOverlap1;
		}
		else {
			fYSmallestOverlap = fYOverlap2;
		}
		if (glm::abs(fYSmallestOverlap) < glm::abs(fSmallestOverlap)) {
			collisionNormal = glm::vec3(0, 1, 0);
			fIntersectDist = fYSmallestOverlap;
			fSmallestOverlap = fYSmallestOverlap;
		}
	}
	else {
		return false;
	}
	if (fCubeMaxZ > fSphereMinZ && fSphereMaxZ > fCubeMinZ) {
		float fZOverlap1 = fCubeMaxZ - fSphereMinZ;
		float fZOverlap2 = fCubeMinZ - fSphereMaxZ;

		if (glm::abs(fZOverlap1) < glm::abs(fZOverlap2)) {
			fZSmallestOverlap = fZOverlap1;
		}
		else {
			fZSmallestOverlap = fZOverlap2;
		}
		if (glm::abs(fZSmallestOverlap) < glm::abs(fSmallestOverlap)) {
			collisionNormal = glm::vec3(0, 0, 1);
			fIntersectDist = fZSmallestOverlap;
			fSmallestOverlap = fZSmallestOverlap;
		}
	}
	else {
		return false;
	}

	sphere->m_position += collisionNormal * fIntersectDist;
	glm::vec3 force = -1 * sphere->m_mass * collisionNormal * (glm::dot(collisionNormal, sphere->m_velocity));
	sphere->ApplyForce(force + force);
	
	return true;
}

