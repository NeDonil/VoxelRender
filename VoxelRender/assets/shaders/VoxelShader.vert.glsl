#version 450 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

layout(location = 2) in vec3 a_Translate;
layout(location = 3) in vec3 a_Color;

uniform mat4 u_View;
uniform mat4 u_Projection;

uniform int light_count;

out vec3 v_Normal;
out vec3 v_FragPos;
out vec3 v_Color;

void main()
{
	mat4 Model;
	Model[0][0] = 1;
	Model[1][1] = 1;
	Model[2][2] = 1;
	Model[3][3] = 1;

	Model[3][0] = a_Translate.x;
	Model[3][1] = a_Translate.y;
	Model[3][2] = a_Translate.z;

	v_Normal = mat3(transpose(inverse(Model))) * a_Normal;
	v_FragPos = vec3(Model * vec4(a_Position, 1.0));
	v_Color = a_Color;

	gl_Position = u_Projection * u_View * Model * vec4(a_Position, 1.0);
}