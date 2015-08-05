#include "TestState.h"
#include "FlyCamera.h"
#include "ShaderLoader.h"
#include <stdio.h>
#include "imgui.h"
#include "aieutilities\Gizmos.h"
#include "Skybox.h"
#include "Utils.h"
#include "physics\Box.h"
#include "physics\Ball.h"
#define IM_ARRAYSIZE(_ARR)          ((int)(sizeof(_ARR)/sizeof(*_ARR)))

void TestState::Init(GLFWwindow* _window, GameStateManager* _gameStateManager) {
	m_window = _window;
	m_gameStateManager = _gameStateManager;
	m_camera = new FlyCamera(10.0f);
	m_camera->SetInputWindow(m_window);
	m_camera->SetPerspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);
	m_camera->SetLookAt(glm::vec3(40, 20, 14), glm::vec3(4, 0, 4), glm::vec3(0, 1, 0));
	SetUpPhysX();
	SetUpVisualDebugger();
	Gizmos::create();
	PxTransform pose = PxTransform(PxVec3(0.0f, 0, 0.0f), PxQuat(PxHalfPi*1.0f, PxVec3(0.0f, 0, 1)));
	PxRigidStatic* plane = PxCreateStatic(*g_Physics, pose, PxPlaneGeometry(), *g_PhysicsMaterial);
	g_PhysicsScene->addActor(*plane);
	for (PxReal i = 0; i < 2; i++) {
		m_box[(int)i] = new Box(PxVec3(i * 3, 13, i * 4), PxVec3(i+1, i+1, i+1), 2.0f, g_PhysicsMaterial, g_Physics, g_PhysicsScene, vec4(0.5f, 0.5f, 1, 1));
	}
	m_ball = new Ball(PxVec3(0, 10, 1), 5, 2, g_PhysicsMaterial, g_Physics, g_PhysicsScene, vec4(1, 0.5f, 0.5f, 1));

	PxVec3 side1(45, 2.5f, 5);
	PxVec3 side2(05, 2.5f, 45);
	m_box[2] = new Box(PxVec3(0, 02.5f, 40), side1, 0, g_PhysicsMaterial, g_Physics, g_PhysicsScene, glm::vec4(1), true);
	m_box[3] = new Box(PxVec3(0, 02.5f, -40), side1, 0, g_PhysicsMaterial, g_Physics, g_PhysicsScene, glm::vec4(1), true);
	m_box[4] = new Box(PxVec3(40, 02.5f, 00), side2, 0, g_PhysicsMaterial, g_Physics, g_PhysicsScene, glm::vec4(1), true);
	m_box[5] = new Box(PxVec3(-40, 02.5f, 00), side2, 0, g_PhysicsMaterial, g_Physics, g_PhysicsScene, glm::vec4(1), true);


	side1 = PxVec3(4.5f, 0.25f, 0.5f);
	side2 = PxVec3(0.5f, 0.25f, 4.5f);
	m_box[6] = new Box(PxVec3(20.0f, 0.25f, 4.0f), side1, 0, g_PhysicsMaterial, g_Physics, g_PhysicsScene, glm::vec4(1), true);
	m_box[7] = new Box(PxVec3(20.0f, 0.25f, -4.0f), side1, 0, g_PhysicsMaterial, g_Physics, g_PhysicsScene, glm::vec4(1), true);
	m_box[8] = new Box(PxVec3(24.0f, 0.25f, 0.0f), side2, 0, g_PhysicsMaterial, g_Physics, g_PhysicsScene, glm::vec4(1), true);
	m_box[9] = new Box(PxVec3(16.0f, 0.25f, 0.0f), side2, 0, g_PhysicsMaterial, g_Physics, g_PhysicsScene, glm::vec4(1), true);

	PxParticleFluid* pf;

	PxU32 maxParticles = 2000;
	bool perParticleRestOffset = false;
	pf = g_Physics->createParticleFluid(maxParticles, perParticleRestOffset);

	pf->setRestParticleDistance(.3f);
	pf->setDynamicFriction(0.1f);
	pf->setStaticFriction(0.1f);
	pf->setDamping(0.1f);
	pf->setParticleMass(0.1f);
	pf->setRestitution(0.0f);
	pf->setParticleBaseFlag(PxParticleBaseFlag::eCOLLISION_TWOWAY, true);
	pf->setStiffness(100.0f);

	if (pf) {
		g_PhysicsScene->addActor(*pf);
		m_particleEmitter = new ParticleFluidEmitter(maxParticles, PxVec3(20, 10, 0), pf, .01f);
		m_particleEmitter->setStartVelocityRange(-0.001f, -250.0f, -0.001f, 0.001f, 250.0f, 0.001f);
	}
	m_ragdoll = new Ragdoll(g_Physics, g_PhysicsScene, g_PhysicsMaterial);
	
	m_character = new CharacterController(g_PhysicsScene, g_PhysicsMaterial, m_window);

	PxShape* shape = g_Physics->createShape(PxBoxGeometry(5, 5, 5), *g_PhysicsMaterial);
	
	m_randomActor = PxCreateStatic(*g_Physics, PxTransform(PxVec3(-10, 5, -10)), PxBoxGeometry(PxVec3(0.1f, 0.1f, 0.1f)), *g_PhysicsMaterial);
	g_PhysicsScene->addActor(*m_randomActor);
	m_triggerVolume = new TriggerVolume(g_PhysicsScene, m_randomActor, shape);
}

TestState::~TestState() {
	delete m_camera;
	g_PhysicsScene->release();
	g_Physics->release();
	g_PhysicsFoundation->release();

	Gizmos::destroy();
}

void TestState::Update(double _dt) {
	m_camera->Update(_dt);

	m_character->Update((float)_dt);

	for (int i = 0; i < 10; i++) {
		m_box[i]->Update(_dt);
	}
	m_ball->Update(_dt);
	if (m_particleEmitter) {
		m_particleEmitter->update((float)_dt);
	}

	if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		m_ragdoll->AddForce(PxVec3(0, 600, 0));
	}
	if (m_triggerVolume->m_triggered) {
		m_ragdoll->WakeUp();
	}
	m_triggerVolume->Update(_dt);



	UpdatePhysX(_dt);
}
void TestState::Draw() {
	glClearColor(0, 0, 0, 1);
	Gizmos::clear();

	glEnable(GL_DEPTH_TEST);
	Gizmos::addAABBFilled(glm::vec3(0, -0.000001f, 0), glm::vec3(1000, 0.000001f, 1000), glm::vec4(0, 0.25f, 0, 1));

	m_character->Draw();
	
	for (int i = 0; i < 10; i++) {
		m_box[i]->Draw();
	}
	
	m_ball->Draw();
	if (m_particleEmitter) {
		m_particleEmitter->renderParticles();
	}
	m_ragdoll->Draw();

	PxU32 nShapes = m_randomActor->getNbShapes();
	PxShape** shapes = new PxShape*[nShapes];
	m_randomActor->getShapes(shapes, nShapes);
	Utils::AddWidget(shapes[0], m_randomActor);

	m_triggerVolume->Draw();

	Gizmos::draw(m_camera->GetProjectionView());
	DrawGUI();
}

void TestState::DrawGUI() {

}

void TestState::SetUpPhysX() {
	PxAllocatorCallback* myCallback = new myAllocator();
	g_PhysicsFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, *myCallback, g_DefaultErrorCallback);
	g_Physics = PxCreatePhysics(PX_PHYSICS_VERSION, *g_PhysicsFoundation, PxTolerancesScale());
	PxInitExtensions(*g_Physics);
	g_PhysicsMaterial = g_Physics->createMaterial(0.5f, 0.5f, 0.5f);
	PxSceneDesc sceneDesc(g_Physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0, -10.0f, 0);
	sceneDesc.filterShader = &PxDefaultSimulationFilterShader;
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	g_PhysicsScene = g_Physics->createScene(sceneDesc);

}
void TestState::SetUpVisualDebugger() {
	if (g_Physics->getPvdConnectionManager() == NULL) {
		return;
	}
	const char* pvd_host_ip = "127.0.0.1";
	int port = 5425;
	unsigned int timeout = 100;
	PxVisualDebuggerConnectionFlags connectionFlags = PxVisualDebuggerExt::getAllConnectionFlags();
	auto theConnection = PxVisualDebuggerExt::createConnection(g_Physics->getPvdConnectionManager(), pvd_host_ip, port, timeout, connectionFlags);
}
void TestState::UpdatePhysX(double _dt) {
	if (_dt <= 0) {
		return;
	}
	g_PhysicsScene->simulate((physx::PxReal)_dt);
	while (g_PhysicsScene->fetchResults() == false) {

	}
}

