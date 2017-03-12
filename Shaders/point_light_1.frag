// Fragment Shader

const int NUM_LIGHTS = 2;

uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 lightVector[NUM_LIGHTS];
varying vec3 fragNormal;

void main()
{
	vec4 total = vec4(0, 0, 0, 0);
	float lightingFactor;
	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		lightingFactor = max(dot(lightVector[i], fragNormal), 0.0);
		total += diffuseColor[i] * lightingFactor;
	}

	gl_FragColor = total;
}
