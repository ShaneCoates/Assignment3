#include "DIYPhysicsState.h"
#include "FlyCamera.h"
#include "ShaderLoader.h"
#include <stdio.h>
#include "imgui.h"
#include "aieutilities\Gizmos.h"
#include "Skybox.h"
#include "Utils.h"
#include "DIYPhysics\Spring.h"

#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))

void PhysicsState::Init(GLFWwindow* _window, GameStateManager* _gameStateManager) {
	m_window = _window;
	m_gameStateManager = _gameStateManager;
	m_camera = new FlyCamera(100.0f);
	m_camera->SetInputWindow(m_window);
	m_camera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_camera->SetLookAt(glm::vec3(100, 100, 100), glm::vec3(4, 0, 4), glm::vec3(0, 1, 0));
	Gizmos::create();

	m_physicsScene = new PhysicsScene();
	m_physicsScene->m_gravity = glm::vec3(0, -9.8, 0);
	m_physicsScene->m_timeStep = 0.001f;
	
	for (float i = 1; i <= 11; i++) {
		m_spheres.push_back(new Sphere(glm::vec3(cosf(i), 30, sinf(i)), glm::vec3(0, 0, 0), i, i * 0.5f, glm::vec4(1, 0, 1, 1)));
	}

	for each (auto itr in m_spheres)
	{
		m_physicsScene->AddActor(itr);
	}

	m_cube[0] = new Cube(glm::vec3(-50, 10, 0), glm::vec3(2, 10, 52), glm::vec3(0), 1000, glm::vec4(1, 1, 1, 1));
	m_cube[1] = new Cube(glm::vec3(0, 10, -50), glm::vec3(52, 10, 2), glm::vec3(0), 1000, glm::vec4(1, 1, 1, 1));
	m_cube[2] = new Cube(glm::vec3(50, 10, 0),  glm::vec3(2, 10, 52), glm::vec3(0), 1000, glm::vec4(1, 1, 1, 1));
	m_cube[3] = new Cube(glm::vec3(0, 10, 50),  glm::vec3(52, 10, 2), glm::vec3(0), 1000, glm::vec4(1, 1, 1, 1));
	
	for (int i = 0; i < 4; i++) {
		m_cube[i]->m_static = true;
		m_physicsScene->AddActor(m_cube[i]);
	}
	m_plane = new Plane(glm::vec3(0, 1, 0), 0);
	m_physicsScene->AddActor(m_plane);

	m_spring = new Spring(Spring(m_spheres[9], m_spheres[10], 0.1f));
	m_physicsScene->AddActor(m_spring);
}

PhysicsState::~PhysicsState() {
	delete m_camera;

	Gizmos::destroy();
}

void PhysicsState::Update(double _dt) {
	m_camera->Update(_dt);

	m_physicsScene->Update(_dt);

}
void PhysicsState::Draw() {
	glClearColor(0, 0, 0, 1);
	Gizmos::clear();
	glEnable(GL_DEPTH_TEST);

	m_physicsScene->Draw();

	Gizmos::draw(m_camera->GetProjectionView());
	DrawGUI();
}

void PhysicsState::DrawGUI() {
	ImGui::SliderFloat("Spring Length", &m_spring->m_distance, 0, 200);
}

