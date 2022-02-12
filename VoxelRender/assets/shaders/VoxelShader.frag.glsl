#version 450 core

layout(location = 0) out vec4 a_Color;

uniform vec3 u_LightPos;
uniform vec3 u_ViewPos;

in vec3 v_Color;
in vec3 v_Normal;
in vec3 v_FragPos;

void main()
{
	float ambientCoff = 0.1;

	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_LightPos - v_FragPos);
	float diffuse = max(dot( norm, lightDir), 0.0);

	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float specular = pow(max(dot(viewDir, reflectDir), 0.0), 2) * 0.5;

	a_Color = vec4((ambientCoff + diffuse + specular) * v_Color, 1.0);
	//a_Color = v_Normal;
}