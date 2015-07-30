#ifndef _CHARACTER_CONTROLLER_H_
#define	_CHARACTER_CONTROLLER_H_
#include "physics\MyControllerHitReport.h"
#include "characterkinematic\PxController.h"
struct GLFWwindow;
class CharacterController {
public:
	CharacterController(physx::PxScene* _scene, physx::PxMaterial* _material, GLFWwindow* _window);
	~CharacterController();

	void Update(float _dt);
	void Draw();
private:
	GLFWwindow* m_window;
	MyControllerHitReport* m_hitReport;
	physx::PxControllerManager* g_characterManager;
	physx::PxController* g_characterController;
	float m_characterYVelocity;
	float m_characterRotation;
	float m_playerGravity;
};

#endif