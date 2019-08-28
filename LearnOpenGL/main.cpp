#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include "graphic/Shader.h"
#include <cassert>
#include "commons/CommonUtils.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "commons/MathType.h"


GLFWwindow* g_win;
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void CursorPosCallback(GLFWwindow* win, double x, double y);
void  ScrollCallback(GLFWwindow* win, double offsetX, double offsetY);
void ProcessInput(GLFWwindow* win);
int InitGLFW();
void Render();
void Update(float dt);

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

GLuint VAO, VBO;
Shader* p_shader;
vec3 g_cameraDir(0,0,1);
vec3 g_cameraPos(0, 0, -5);


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

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
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
	p_shader = new Shader("shaders/triangle.vert", "shaders/triangle.frag");
	const auto pTexture_1 = new Texture("resources/texture/container.jpg");
	const auto pTexture_2 = new Texture("resources/texture/huaji.jpg");
	p_shader->AddTexture(pTexture_1);
	p_shader->AddTexture(pTexture_2);

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f
	};

	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, reinterpret_cast<void*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	p_shader->Use();

	mat4x4 model = mat4x4(1.0f);
	mat4x4 view = mat4x4(1.0f);
	mat4x4 proj = mat4x4(1.0f);

	model = glm::rotate(model, glm::radians(50.0f), vec3_left);
	view = translate(view, vec3(0, 0, -5.0f));
	proj = glm::perspective(
		glm::radians(45.0f),
		static_cast<float>(SCREEN_WIDTH) / static_cast<float>(SCREEN_HEIGHT),
		0.1f,
		100.0f);
	p_shader->SetMat4vf("model", glm::value_ptr(model));
	p_shader->SetMat4vf("view", glm::value_ptr(view));
	p_shader->SetMat4vf("proj", glm::value_ptr(proj));


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

	glBindVertexArray(VAO);
	for (int i = 0; i < 10; ++i)
	{
		mat4x4 model(1.0f);
		model = glm::translate(model, cubePositions[i]);
		model = glm::rotate(model, i * 20.0f, vec3_one);
		p_shader->SetMat4vf("model", glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
	glBindVertexArray(0);
}

void Update(float dt)
{
	mat4x4 view = glm::lookAtRH(g_cameraPos, g_cameraPos + g_cameraDir, vec3_up);
	p_shader->SetMat4vf("view", glm::value_ptr(view));
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
	// std::cout << '(' << x << ',' << y << ')' << std::endl;

	//计算相机方向
	static float yaw = 0;
	static float pitch = 0;

	float speed = 0.1f;
	
	static vec3 prevPos(x, y, 0);
	vec3 dir = vec3(x, y, 0) - prevPos;
	dir.y *= -1;
	prevPos.x = x;
	prevPos.y = y;

	yaw += dir.x * speed;
	pitch += dir.y * speed;

	pitch = CommonUtils::Clamp(pitch, -89.0f, 89.0);

	g_cameraDir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	g_cameraDir.y = sin(glm::radians(pitch));
	g_cameraDir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	g_cameraDir = glm::normalize(g_cameraDir);
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
	if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)
	{
		g_cameraPos +=  moveSpd * CommonUtils::s_time->deltaTime * g_cameraDir;
	}
	else if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
	{
		g_cameraPos +=  moveSpd * CommonUtils::s_time->deltaTime * glm::cross(vec3_up, g_cameraDir);
	}
	else if (glfwGetKey(win,GLFW_KEY_S) == GLFW_PRESS)
	{
		g_cameraPos -= moveSpd * CommonUtils::s_time->deltaTime * g_cameraDir;
	}
	else if (glfwGetKey(win,GLFW_KEY_D) == GLFW_PRESS)
	{
		g_cameraPos -= moveSpd * CommonUtils::s_time->deltaTime * glm::cross(vec3_up, g_cameraDir);
	}

}

int InitGLFW();

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
