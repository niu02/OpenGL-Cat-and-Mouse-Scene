#version 330 core

out vec4 fragCol;

in vec3 col;
in vec2 tex;

uniform sampler2D Texture1;


void main()
{
	if (tex != 0)
	{
		fragCol = texture(Texture1, tex);
	}
	else
	{
		fragCol = vec4(col, 1.0f);
	}
}
