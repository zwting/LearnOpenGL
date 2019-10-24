#version 430 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 FragNormal;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;

uniform vec3 ambient;    //环境光
uniform vec3 light0_dir; //平行光

void main()
{
	vec4 texColor = texture(texture0, TexCoord);

	FragColor = texColor;
}