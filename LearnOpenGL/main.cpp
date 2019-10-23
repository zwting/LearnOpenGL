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
		vec3(0, 0, 5),
		VEC3_ZERO,
		45.0f,
		static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
		0.1f,
		100.0f
	);

	g_pCamera->Active();

	vec3 cubePositions[] = {
		vec3(0.0f, 0.0f, 0.0f),
		vec3(2.0f, 5.0f, -15.0f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.0f, -12.3f),
		vec3(2.4f, -0.4f, -3.5f),
		vec3(-1.7f, 3.0f, -7.5f),
		vec3(1.3f, -2.0f, -2.5f),
		vec3(1.5f, 2.0f, -2.5f),
		vec3(1.5f, 0.2f, -1.5f),
		vec3(-1.3f, 1.0f, -1.5f)
	};

	for (int i = 0; i < 10; ++i)
	{
		auto cube = PrimitiveModel::CreatePrimitive(PrimitiveModel::PrimitiveType::Cube);
		cube->SetPosition(cubePositions[i]);
		cube->SetRotation(glm::angleAxis(glm::radians((i + 1) * 20.0f), VEC3_ONE));

		auto modelCube = cube->GetModel();
		if (modelCube)
		{
			const auto meshes = modelCube->GetMeshList();
			if (!meshes.empty())
			{
				meshes[0]->AddTexture(MeshTexture("resources/texture/brick.jpg"));
			}
		}

		nodeList.push_back(cube);
	}

	Model* soldier = new Model("resources/model/nanosuit/nanosuit.obj");
	Node* node = new Node(VEC3_ZERO, QUA_IDENTITY);
	node->SetModel(soldier);
	node->SetScale(VEC3_ONE * 0.5f);
	nodeList.push_back(node);

	Node* plane = PrimitiveModel::CreatePrimitive(PrimitiveModel::PrimitiveType::Quad);
	if(plane)
	{
		auto planeMode  = plane->GetModel();
		if(planeMode)
		{
			planeMode->GetMeshList()[0]->AddTexture(MeshTexture("resources/texture/grass.png"));
		}
	}

	p_shader = new Shader("shaders/triangle.vert", "shaders/triangle.frag");
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
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	//渲染对象的同时填充模板
	glStencilFunc(GL_ALWAYS, 1, 0xff);
	glStencilMask(0xff);

	p_shader->Use();
	for (int i = 0; i < nodeList.size(); ++i)
	{
		nodeList[i]->SetScale(VEC3_ONE);
		nodeList[i]->Render(Shader::CurShader);
	}

	//渲染描边, 不修改模板，关闭深度测试
	glStencilFunc(GL_NOTEQUAL, 1, 0xff);
	glStencilMask(0);
	glDisable(GL_DEPTH_TEST);

	p_solidColorShader->Use();

	for (int i = 0; i < nodeList.size(); ++i)
	{
		nodeList[i]->SetScale(VEC3_ONE * 1.1f);
		nodeList[i]->Render(Shader::CurShader);
	}
	glEnable(GL_DEPTH_TEST);
	glStencilMask(0xff);
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
