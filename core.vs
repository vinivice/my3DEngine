#version 330 core
layout ( location = 0 ) in vec3 vertexPosition;
layout ( location = 1 ) in vec3 vertexColor;
layout ( location = 2 ) in vec3 vertexNormal;
layout ( location = 3 ) in vec4 vertexLightConstants;


out vec3 ourColor;

uniform mat4 model[10];
uniform mat4 view;
uniform mat4 projection;
uniform int level;
uniform vec3 lightPower;
uniform vec3 lightPosition;
uniform vec4 temporaryLightConstants;


void main( )
{
	
	mat4 endModel = mat4(1.0);
	int i;
	for(i = 0; i <= level; i++)
	{
		endModel = endModel*model[i];
	}
	
	mat4 modelView = view*endModel;
	vec4 vertexPositionView = modelView*vec4(vertexPosition, 1.0 );
	vec4 lightPositionView = view*vec4(lightPosition, 1.0 );

	vec3 L = lightPositionView.xyz - vertexPositionView.xyz;
	float distance2 = dot(L, L);
	L = normalize(L);
	vec3 V = normalize(-vertexPositionView.xyz);
	mat3 normalMatrix = transpose(inverse(mat3(modelView)));
	vec3 N = normalize(normalMatrix*vertexNormal);
	//vec3 R = normalize(reflect(-L, N));
	
	vec3 intensityArrived = lightPower / (12.57*distance2);

	float diffuseComponent = max(0.0f, dot(L, N));
	/*float diffuseComponent;
	if(dot(L, N) < 0.0f)
	{ 
		diffuseComponent = max(0.0f, -dot(L, N));
	}
	else
	{
		diffuseComponent = max(0.0f, dot(L, N));
	}*/
	//float speularComponent


	vec3 ambient = temporaryLightConstants[0]*intensityArrived; //Average of all light sources
	vec3 diffuse = temporaryLightConstants[1]*intensityArrived*diffuseComponent;
	//vec3 specular = temporaryLightConstants[2]*intensityArrived*specularComponent

	gl_Position = projection*vertexPositionView;

	ourColor = vertexColor*(diffuse);	
}