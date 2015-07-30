#include "physics\CharacterController.h"
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "Utils.h"
using namespace physx;
CharacterController::CharacterController(physx::PxScene* _scene, physx::PxMaterial* _material, GLFWwindow* _window) {
	m_window = _window;
	m_hitReport = new MyControllerHitReport();
	g_characterManager = PxCreateControllerManager(*_scene);

	PxCapsuleControllerDesc desc;
	desc.height = 1.6f;
	desc.radius = 0.4f;
	desc.position.set(0, 0, 10);
	desc.material = _material;
	desc.reportCallback = m_hitReport;
	desc.density = 10;

	g_characterController = g_characterManager->createController(desc);
	g_characterController->setPosition(PxExtendedVec3(0, 0, 0));
	m_characterYVelocity = 0;
	m_characterRotation = 0;
	m_playerGravity = -0.5f;
	m_hitReport->clearPlayercontactNormal();
}
CharacterController::~CharacterController() {

}
void CharacterController::Update(double _dt) {
	bool onGround;
	float movementSpeed = 10.0f;
	float rotationSpeed = 1.0f;
	if (m_hitReport->getPlayerContactNormal().y > 0.3f)
	{
		m_characterYVelocity = -0.1f;
		onGround = true;
	}
	else
	{
		m_characterYVelocity += m_playerGravity * _dt;
		onGround = false;
	}
	m_hitReport->clearPlayercontactNormal();
	const PxVec3 up(0, 1, 0);
	PxVec3 velocity(0, m_characterYVelocity, 0);
	if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		velocity.x -= movementSpeed*_dt;
	}
	if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		velocity.x += movementSpeed*_dt;
	}
	if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		velocity.z -= movementSpeed*_dt;
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		velocity.z += movementSpeed*_dt;
	}
	float minDistance = 0.001f;
	PxControllerFilters filter;
	g_characterController->move(velocity, minDistance, _dt, filter);
}
void CharacterController::Draw() {
	PxU32 nShapes = g_characterController->getActor()->getNbShapes();
	PxShape** shapes = new PxShape*[nShapes];
	g_characterController->getActor()->getShapes(shapes, nShapes);
	while (nShapes--) {
		Utils::AddWidget(shapes[nShapes], g_characterController->getActor());
	}
}