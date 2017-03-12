// Vertex Shader

const int NUM_LIGHTS = 2;

uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 fragNormal;
varying vec3 lightVector[NUM_LIGHTS];
uniform vec3 eyeSpaceLightVector[NUM_LIGHTS];

void main()
{
	vec3 eyeSpaceVertex = vec3(gl_ModelViewMatrix * gl_Vertex);
	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		lightVector[i] = vec3(normalize(eyeSpaceLightVector[i] - eyeSpaceVertex));
	}

	fragNormal = normalize(gl_NormalMatrix * gl_Normal);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
