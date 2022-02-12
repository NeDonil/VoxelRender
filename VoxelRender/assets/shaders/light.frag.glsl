#version 450 core

layout(location = 0) out vec4 a_Color;

uniform vec4 u_Color;
uniform vec3 u_LightPos;

in vec4 v_Normal;

void main()
{
	float ambientCoff = 0.2;

	float diffuse = max(dot( v_Normal, normalize(vec4(u_LightPos, 1.0))), 0.0);

	a_Color = (ambientCoff + diffuse ) * u_Color;
}