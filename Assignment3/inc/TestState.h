/*
	Author: Shane Coates
	Description: Test Game State - Remove before release
*/

#ifndef _TEST_GAMESTATE_H_
#define	_TEST_GAMESTATE_H_

#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "GameStateManager.h"
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include <PxPhysicsAPI.h>
#include <PxScene.h>
#include <pvd\PxVisualDebugger.h>
using namespace physx;

struct GLFWwindow;
class FlyCamera;
class Skybox;
class Box;
class Ball;
class myAllocator : public PxAllocatorCallback {
public:
	virtual ~myAllocator() {}
	virtual void* allocate(size_t size, const char* typeName, const char* filename, int line) {
		void* pointer = _aligned_malloc(size, 16);
		return pointer;
	}
	virtual void deallocate(void* ptr) {
		_aligned_free(ptr);
	}
};
class TestState : public IGameState
{
public:
	//Constructor inherits from IGameState and calls the Init function
	TestState(GLFWwindow* _window, GameStateManager* _gameStateManager) : IGameState()
	{
		Init(_window, _gameStateManager);
	}
	//Destructor
	~TestState();

	//Initialise the gamestate
	void Init(GLFWwindow* _window, GameStateManager* _gameStateManager);

	//Update/Draw functions
	void Update(double _dt);
	void Draw();

private:

	void DrawGUI();

	void SetUpPhysX();
	void SetUpVisualDebugger();
	void UpdatePhysX(double _dt);

	PxFoundation* g_PhysicsFoundation;
	PxPhysics* g_Physics;
	PxScene* g_PhysicsScene;
	PxDefaultErrorCallback g_DefaultErrorCallback;
	PxDefaultAllocator g_DefaultAllocatorCallback;
	PxSimulationFilterShader g_DefaultFilterShader = PxDefaultSimulationFilterShader;
	PxMaterial* g_PhysicsMaterial;
	PxMaterial* g_boxMaterial;
	PxCooking* g_PhysicsCooker;


	GLFWwindow* m_window;
	GameStateManager* m_gameStateManager;

	FlyCamera* m_camera;

	Skybox* m_skybox;

	Box* m_box[10];
	Ball* m_ball;
};

#endif