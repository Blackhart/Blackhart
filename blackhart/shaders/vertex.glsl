#version 430 core

layout(location = 0) in vec3		in_position;

layout(location = 1) uniform mat4	uni_mvp;


void	main()
{
	gl_Position = uni_mvp * vec4(in_position.xyz, 1.0f);
}