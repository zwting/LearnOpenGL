#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include "graphic/Shader.h"
#include <cassert>
#include "commons/CommonUtils.h"
#include "glm/glm.hpp"
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

Camera* g_pCamera;
Node* cube;
vec3 lightDir(1, 0, 0);


void InitData();

void CleanData();

int main()
{
	if (InitGLFW() == -1)
		return -1;

	InitData();

	while (!glfwWindowShouldClose(g_win))
	{
		CommonUtils::s_time->UpdateTime(glfwGetTime());

		ProcessInput(g_win);

		Update(CommonUtils::s_time->deltaTime);

		glClearColor(0.1f, 0.1f, 0.1f, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Render();

		glfwSwapBuffers(g_win);
		glfwPollEvents();
	}

	CleanData();
	glfwTerminate();
	return 0;
}


//初始化数据
void InitData()
{
	g_pCamera = new Camera(
		vec3(0, 0, 5),
		vec3_zero,
		45.0f,
		static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
		0.1f,
		100.0f
	);

	cube = PrimitiveModel::CreatePrimitive(PrimitiveModel::PrimitiveType::Cube);
	cube->SetPosition(vec3(1, 1, -3));
	// cube->setRotation(glm::angleAxis(glm::radians(45.0f), vec3_up));
	auto modelCube = cube->GetModel();
	if (modelCube)
	{
		const auto meshes = modelCube->GetMeshList();
		if (!meshes.empty())
		{
			meshes[0]->AddTexture(MeshTexture("resources/texture/brick.jpg"));
		}
	}

	p_shader = new Shader("shaders/triangle.vert", "shaders/triangle.frag");
	// p_shader->AddTexture(pTexture_1);
	// p_shader->AddTexture(pTexture_2);

	p_shader->Use();

	p_shader->SetMat4vf("proj",value_ptr(g_pCamera->GetProjMatrix()));
	p_shader->SetMat4vf("view",value_ptr(g_pCamera->GetViewMatrix()));
	p_shader->SetVec3("light0_dir", lightDir);


	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
}

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


//渲染
void Render()
{
	float t = CommonUtils::s_time->time;
	float greenVal = sin(t) * 0.5f + 0.5f;
	cube->Render(p_shader);
}

void Update(float dt)
{
	p_shader->SetMat4vf("view",value_ptr(g_pCamera->GetViewMatrix()));
	float speed = 30;
	static float angle = 0;
	angle += speed * dt;
	auto q = glm::angleAxis(glm::radians(angle), vec3_up);
	std::cout << "angle=" << angle << ", deltaTime=" << dt << ",fps:" << 1 / dt << std::endl;
	cube->SetRotation(q);
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
	//计算相机方向
	static float yaw = 0;
	static float pitch = 0;

	float speed = 0.1f;

	static vec3 prevPos(x, y, 0);
	vec3 delta = vec3(x, y, 0) - prevPos;
	delta *= 0.4f;
	prevPos.x = x;
	prevPos.y = y;

	// std::cout << delta.x << ", " << delta.y << std::endl;
	quaternion qx = glm::angleAxis(glm::radians(delta.x),vec3_up);
	quaternion qy = glm::angleAxis(glm::radians(delta.y),vec3_right);

	g_pCamera->Rotate(qx * qy);
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
	else if(glfwGetKey(win, GLFW_KEY_KP_5) ==GLFW_PRESS)
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
