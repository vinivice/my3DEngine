#version 330 core
layout ( location = 0 ) in vec3 position;
layout ( location = 1 ) in vec3 color;

out vec3 ourColor;

uniform mat4 model[10];
uniform mat4 view;
uniform mat4 projection;
uniform int level;

void main( )
{
	mat4 endModel = mat4(1.0);
	int i;
	for(i = 0; i <= level; i++)
	{
		endModel = endModel*model[i];
	}

	gl_Position = projection*view*endModel*vec4(position, 1.0 );

	ourColor = color;	
}