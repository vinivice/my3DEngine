#version 330 core

struct Light
{
	vec3 lightPower;
	vec3 lightPosition;
};

layout ( location = 0 ) in vec3 vertexPosition;
layout ( location = 1 ) in vec3 vertexColor;
layout ( location = 2 ) in vec3 vertexNormal;
layout ( location = 3 ) in vec4 vertexLightConstants;


out vec3 ourColor;

uniform mat4 model[10];
uniform mat4 view;
uniform mat4 projection;
uniform int level;
uniform Light light;
uniform vec4 temporaryLightConstants;


void main( )
{
	/*
	vec3 L = light.position - vertexPosition;
	float distance2 = dot(L, L);
	vec3 intensityArrived = light.power / (12.57*distance2);
	float ambientIntensity = intensityArrived; //Sum of all light sources
	*/

	mat4 endModel = mat4(1.0);
	int i;
	for(i = 0; i <= level; i++)
	{
		endModel = endModel*model[i];
	}

	gl_Position = projection*view*endModel*vec4(vertexPosition, 1.0 );

	ourColor = vertexColor;	
}