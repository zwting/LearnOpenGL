#version 430 core

layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aNormal;
layout(location=2) in vec2 aTexCoord;

uniform float offsetX;
uniform mat4x4 model;
uniform mat4x4 view;
uniform mat4x4 proj;


out vec2 TexCoord;
out vec3 FragPos;
out vec3 FragNormal;

mat4x4 mvp;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	FragNormal = transpose(inverse(mat3(model))) * aNormal;
	TexCoord = aTexCoord;
	gl_Position = proj * view * vec4(FragPos,1.0);
}