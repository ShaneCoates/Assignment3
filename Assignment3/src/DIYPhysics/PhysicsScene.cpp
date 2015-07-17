#include "DIYPhysics\PhysicsScene.h"
#include "DIYPhysics\Sphere.h"
#include "DIYPhysics\Plane.h"
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
	for each (PhysicsObject* obj in m_actors)
	{
		obj->Update(m_gravity, _dt);
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
			sphere1->m_position += (seperationVector * (sphere1->m_mass / totalMass));
			sphere2->m_position += (seperationVector * (sphere2->m_mass / totalMass));
			
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

		if (sphereToPlane < 0) {
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}

		float intersection = sphere->m_radius = sphereToPlane;

		if (intersection > 0) {
			glm::vec3 relativeVelocity = sphere->m_velocity;
			glm::vec3 planeNormal = collisionNormal;
			glm::vec3 forceVector = -1 * sphere->m_mass * planeNormal * (glm::dot(planeNormal, sphere->m_velocity));

			sphere->ApplyForce(forceVector * glm::vec3(2));
			sphere->m_position += collisionNormal * intersection* 0.5f;

			return true;
		}
	}
	return false;
}