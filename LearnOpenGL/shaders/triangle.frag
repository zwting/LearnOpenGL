#version 430 core
out vec4 FragColor;

in vec4 vertexPos;
in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float factor;

void main()
{
	vec4 t1 = texture(texture0, TexCoord);
	//vec4 t2 = texture(texture1, TexCoord);
	FragColor = t1;
}
