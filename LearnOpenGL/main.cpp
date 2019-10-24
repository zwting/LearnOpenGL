#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include "graphic/Shader.h"
#include <cassert>
#include "commons/CommonUtils.h"
#include "glm/gtc/type_ptr.hpp"
#include "commons/MathType.h"
#include "commons/Camera.h"
#include "commons/PrimitiveModel.h"


GLFWwindow* g_win;
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void CursorPosCallback(GLFWwindow* win, double x, double y);
void ScrollCallback(GLFWwindow* win, double offsetX, double offsetY);
void ProcessInput(GLFWwindow* win);
int InitGLFW();
void Render();
void Update(float dt);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

GLuint VAO, VBO;
Shader* p_shader;
Shader* p_solidColorShader;

Camera* g_pCamera;
vec3 lightDir(1, 1, 1);
std::vector<Node*> nodeList;


void InitAppData();

void CleanData();

void InitOpenGLData();

int main()
{
	if (InitGLFW() == -1)
		return -1;

	InitOpenGLData();
	InitAppData();


	while (!glfwWindowShouldClose(g_win))
	{
		CommonUtils::s_time->UpdateTime(glfwGetTime());

		ProcessInput(g_win);

		Update(CommonUtils::s_time->deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1);

		int clearFlag = GL_COLOR_BUFFER_BIT;
		if (glIsEnabled(GL_DEPTH_TEST)) clearFlag |= GL_DEPTH_BUFFER_BIT;
		if (glIsEnabled(GL_STENCIL_TEST)) clearFlag |= GL_STENCIL_BUFFER_BIT;

		glClear(clearFlag);

		Render();

		glfwSwapBuffers(g_win);
		glfwPollEvents();
	}

	CleanData();
	glfwTerminate();
	return 0;
}

void InitOpenGLData()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	// glEnable(GL_FRAMEBUFFER_SRGB);
}

//初始化数据
void InitAppData()
{
	g_pCamera = new Camera(
		vec3(5, 2.5f, 5),
		VEC3_ZERO,
		45.0f,
		static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
		0.1f,
		100.0f
	);

	g_pCamera->Active();

	vec3 cubePositions[] = {
		vec3(-1.5f, 0, 0),
		vec3(1.5f, 0, -2.5),
	};

	const auto meshTexture = MeshTexture("resources/texture/brick.jpg", GL_CLAMP_TO_EDGE);
	const auto floorTexture = MeshTexture("resources/texture/metal.png", GL_CLAMP_TO_EDGE);

	//创建一个地面
	auto ground = PrimitiveModel::CreatePrimitive(PrimitiveModel::PrimitiveType::Quad);
	ground->SetScale(vec3(35, 35, 1));
	ground->SetPosition(0, -1, 0);
	ground->SetRotation(glm::angleAxis(glm::radians(-90.0f), VEC3_RIGHT));
	ground->GetModel()->GetMeshList()[0]->AddTexture(floorTexture);

	nodeList.push_back(ground);

	int size = sizeof(cubePositions) / sizeof(vec3);
	for (int i = 0; i < size; ++i)
	{
		auto quad = PrimitiveModel::CreatePrimitive(PrimitiveModel::PrimitiveType::Cube);
		cubePositions[i].y = 0;
		quad->SetPosition(cubePositions[i]);

		auto modelCube = quad->GetModel();
		if (modelCube)
		{
			const auto meshes = modelCube->GetMeshList();
			if (!meshes.empty())
			{
				meshes[0]->AddTexture(meshTexture);
			}
		}

		nodeList.push_back(quad);
	}


	//创建一坨草
	

	//
	// Model* soldier = new Model("resources/model/nanosuit/nanosuit.obj");
	// Node* node = new Node(VEC3_ZERO, QUA_IDENTITY);
	// node->SetModel(soldier);
	// node->SetScale(VEC3_ONE * 0.5f);
	// nodeList.push_back(node);

	// Node* plane = PrimitiveModel::CreatePrimitive(PrimitiveModel::PrimitiveType::Quad);
	// nodeList.push_back(plane);
	// plane->SetPosition(6,6,6);
	// if(plane)
	// {
	// 	auto planeMode  = plane->GetModel();
	// 	if(planeMode)
	// 	{
	// 		planeMode->GetMeshList()[0]->AddTexture(MeshTexture("resources/texture/grass.png"));
	// 	}
	// }

	p_shader = new Shader("shaders/triangle.vert", "shaders/grass.frag");
	p_solidColorShader = new Shader("shaders/solidcolor.vert", "shaders/solidcolor.frag");

	p_shader->Use();
	p_solidColorShader->SetMat4vf("proj",VALUE_PTR(g_pCamera->GetProjMatrix()));
	p_solidColorShader->SetMat4vf("view",VALUE_PTR(g_pCamera->GetViewMatrix()));

	p_shader->SetMat4vf("proj",VALUE_PTR(g_pCamera->GetProjMatrix()));
	p_shader->SetMat4vf("view",VALUE_PTR(g_pCamera->GetViewMatrix()));


	p_shader->SetVec3("light0_dir", lightDir);
}


//渲染
void Render()
{
	p_shader->Use();
	for (int i = 0; i < nodeList.size(); ++i)
	{
		nodeList[i]->Render(Shader::CurShader);
	}
}

void Update(float dt)
{
	// p_shader->SetMat4vf("view",VALUE_PTR(g_pCamera->GetViewMatrix()));
	// p_solidColorShader->SetMat4vf("view", VALUE_PTR(g_pCamera->GetViewMatrix()));
	float speed = 30;
	static float angle = 0;
	angle += speed * dt;
	auto q = glm::angleAxis(glm::radians(angle), VEC3_UP);
	// std::cout << "angle=" << angle << ", deltaTime=" << dt << ",fps:" << 1 / dt << std::endl;
	// cube->SetRotation(q);
}


//清理数据
void CleanData()
{
	delete p_shader;
	glDeleteVertexArrays(1, &VAO);
}


void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

//获取鼠标光标位置
void CursorPosCallback(GLFWwindow* win, double x, double y)
{
	float speed = 2.0f;

	static vec3 prevPos(x, y, 0);
	vec3 delta = vec3(x, y, 0) - prevPos;
	delta = delta * speed * CommonUtils::s_time->deltaTime;
	prevPos.x = x;
	prevPos.y = y;

	delta *= -1;

	quaternion qx = glm::angleAxis(glm::radians(delta.x), g_pCamera->GetNode()->GetUp());
	quaternion qy = glm::angleAxis(glm::radians(delta.y), g_pCamera->GetNode()->GetRight());

	vec3 forward = g_pCamera->GetForward();

	std::cout << "(" << delta.x << ", " << delta.y << ")\n";

	forward = qx * qy * forward;

	vec3 target = g_pCamera->GetNode()->GetPosition() + forward * 10.0f;
	g_pCamera->LookAt(target);
}

void ScrollCallback(GLFWwindow* win, double offsetX, double offsetY)
{
}

void ProcessInput(GLFWwindow* win)
{
	if (glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(win, true);
	}

	static float moveSpd = 5.0f;
	auto cameraPos = g_pCamera->GetPosition();
	auto node = g_pCamera->GetNode();
	bool isMove = false;
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += moveSpd * CommonUtils::s_time->deltaTime * g_pCamera->GetForward();
		isMove = true;
	}
	else if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
	{
		// cameraPos += moveSpd * CommonUtils::s_time->deltaTime * glm::cross(vec3_up, node->getForward());
		cameraPos -= moveSpd * CommonUtils::s_time->deltaTime * node->GetRight();
		isMove = true;
	}
	else if (glfwGetKey(win,GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= moveSpd * CommonUtils::s_time->deltaTime * g_pCamera->GetForward();
		isMove = true;
	}
	else if (glfwGetKey(win,GLFW_KEY_D) == GLFW_PRESS)
	{
		// cameraPos -= moveSpd * CommonUtils::s_time->deltaTime * glm::cross(vec3_up, node->getForward());
		cameraPos += moveSpd * CommonUtils::s_time->deltaTime * node->GetRight();
		isMove = true;
	}
	else if (glfwGetKey(win, GLFW_KEY_KP_8) == GLFW_PRESS)
	{
		cameraPos += moveSpd * CommonUtils::s_time->deltaTime * node->GetUp();
		isMove = true;
	}
	else if (glfwGetKey(win, GLFW_KEY_KP_5) == GLFW_PRESS)
	{
		cameraPos -= moveSpd * CommonUtils::s_time->deltaTime * node->GetUp();
		isMove = true;
	}
	if (isMove)
	{
		g_pCamera->SetPosition(cameraPos);
	}
}

int InitGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	g_win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (g_win == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(g_win);
	glfwSetCursorPosCallback(g_win, CursorPosCallback);
	glfwSetScrollCallback(g_win, ScrollCallback);
	glfwSetFramebufferSizeCallback(g_win, FrameBufferSizeCallback);

	glfwSetInputMode(g_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		int code = glfwGetError(nullptr);
		std::cout << "Failed to initialize GLAD" << code << std::endl;
		char buffer[1024];
		return -1;
	}
	return 0;
}
