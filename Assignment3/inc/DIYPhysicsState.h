/*
Author: Shane Coates
Description: Test Game State - Remove before release
*/

#ifndef _DIY_PHYSICS_GAMESTATE_H_
#define	_DIY_PHYSICS_GAMESTATE_H_

#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#include "GameStateManager.h"
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>
#include "DIYPhysics\PhysicsScene.h"
#include "DIYPhysics\Sphere.h"
#include "DIYPhysics\Plane.h"
#include "DIYPhysics\Cube.h"
#include <vector>
struct GLFWwindow;
class FlyCamera;
class Skybox;
class PhysicsState : public IGameState
{
public:
	//Constructor inherits from IGameState and calls the Init function
	PhysicsState(GLFWwindow* _window, GameStateManager* _gameStateManager) : IGameState()
	{
		Init(_window, _gameStateManager);
	}
	//Destructor
	~PhysicsState();

	//Initialise the gamestate
	void Init(GLFWwindow* _window, GameStateManager* _gameStateManager);

	//Update/Draw functions
	void Update(double _dt);
	void Draw();

private:

	void DrawGUI();

	GLFWwindow* m_window;
	GameStateManager* m_gameStateManager;

	FlyCamera* m_camera;

	Skybox* m_skybox;

	PhysicsScene* m_physicsScene;

	std::vector<Sphere*> m_spheres;
	Cube* m_cube[4];
	Plane* m_plane;

};

#endif