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
struct GLFWwindow;
class FlyCamera;
class NetworkManager;
class CheckerBoard;
class Skybox;
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
	void UpdateCamera(double _dt);
	GLFWwindow* m_window;
	GameStateManager* m_gameStateManager;

	FlyCamera* m_camera;

	NetworkManager* m_networkServer;
	NetworkManager* m_networkClient;
	std::string m_clientName;
	std::string m_serverIP;
	unsigned int m_serverPort;

	bool m_serverRunning;

	CheckerBoard* m_checkerBoard;
	Skybox* m_skybox;
	double m_targetCameraAngle;
	const double m_redTargetCameraAngle = M_PI;
	const double m_blackTargetCameraAngle = M_PI * 2;
	double m_cameraAngle;
	bool m_allocatedSide;
	bool m_spinning;
	double m_networkSleepTimer;
};

#endif