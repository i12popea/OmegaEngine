// Vertex Shader

const int NUM_LIGHTS = 32;

uniform int NumLights;
uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 fragNormal;
varying vec3 eyeSpaceVertex;
varying vec3 lightVector[NUM_LIGHTS];
uniform vec3 eyeSpaceLightVector[NUM_LIGHTS];

void main()
{
	gl_TexCoord[0] = gl_MultiTexCoord0;

	eyeSpaceVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	for(int i = 0; i < NumLights; i++)
	{
		lightVector[i] = vec3(normalize(eyeSpaceLightVector[i]));
	}

	fragNormal = normalize(gl_NormalMatrix * gl_Normal);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
