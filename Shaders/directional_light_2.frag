// Fragment Shader

const int NUM_LIGHTS = 2;

uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 lightVector[NUM_LIGHTS];
varying vec3 fragNormal;
varying vec3 eyeSpaceVertex;

void main()
{
	vec4 total = vec4(0, 0, 0, 0);
	vec3 eyeVecNormal = normalize(-eyeSpaceVertex);
	float lightingFactor;
	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		lightingFactor = max(dot(lightVector[i], fragNormal), 0.0);

		vec4 diffuse = diffuseColor[i] * lightingFactor;

		vec3 reflectVec = normalize(-reflect(lightVector[i], fragNormal));
		vec4 specularColor = min(diffuseColor[i] + 0.5, 1);
		vec4 specular = specularColor * pow(max(dot(reflectVec, eyeVecNormal), 0.0), 32.0f);
		specular = clamp(specular, 0.0, 1.0);

		//total += diffuseColor[i] * lightingFactor;
		total += vec4(0.1, 0.1, 0.1, 1) + diffuse + specular;
	}

	gl_FragColor = total;
}
