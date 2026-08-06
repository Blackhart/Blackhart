#version 430 core

layout(location = 0) in vec3		in_position;
layout(location = 1) in vec3		in_color;

layout(location = 1) uniform mat4	uni_mvp;

out vec3	v_color;

void	main()
{
	v_color = in_color;
	gl_Position = uni_mvp * vec4(in_position.xyz, 1.0f);
}
