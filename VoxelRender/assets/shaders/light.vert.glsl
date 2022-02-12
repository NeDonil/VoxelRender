#version 450 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec4 v_Normal;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * vec4(a_Position, 1.0);
	v_Normal = u_Model * vec4(a_Position, 1.0);
	v_Normal = vec4(a_Position, 1.0);
}