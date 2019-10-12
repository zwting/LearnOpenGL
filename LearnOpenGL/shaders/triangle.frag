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
	vec4 c = texture(texture0, TexCoord);
	vec4 c2 = texture(texture1, TexCoord);
	vec3 lightDir = normalize(light0_dir);
	vec3 normal = normalize(FragNormal);
	float diffuse = max(dot(normal, lightDir), 0) * 0.5 + 0.5;

	FragColor = vec4(c.rgb * diffuse, 1.0);
}
