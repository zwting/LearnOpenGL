#version 430 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;

uniform float offsetX;
uniform mat4x4 model;
uniform mat4x4 view;
uniform mat4x4 proj;


out vec2 TexCoord;

mat4x4 mvp;

void main()
{
	mvp = proj * view * model;
	vec4 vertexPos = mvp * vec4(aPos, 1.0);
    gl_Position = vertexPos;
	TexCoord = aTexCoord;
}