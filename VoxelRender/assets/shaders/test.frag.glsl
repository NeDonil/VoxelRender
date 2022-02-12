#version 450 core

layout(location = 0) out vec4 a_Color;

uniform vec4 u_Color;

void main()
{
	a_Color = u_Color;
}