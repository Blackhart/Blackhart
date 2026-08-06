#version 430 core

in vec3		v_color;

out vec4	Color;

void	main()
{
	Color = vec4(v_color, 1.0f);
}
