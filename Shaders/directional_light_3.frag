// Fragment Shader

/*const int NUM_LIGHTS = 1;

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
		vec4 ambient = vec4(0.1, 0.1, 0.1, 1) * gl_FrontMaterial.ambient;

		lightingFactor = max(dot(lightVector[i], fragNormal), 0.0);
		vec4 diffuse = (gl_FrontMaterial.diffuse * diffuseColor[i]) * lightingFactor;

		vec3 reflectVec = normalize(-reflect(lightVector[i], fragNormal));
		vec4 specularColor = min(diffuseColor[i] + 0.5, 1);
		vec4 specular = specularColor * pow(max(dot(reflectVec, eyeVecNormal), 0.0), 32.0f);
		specular = clamp(specular, 0.0, 1.0);

		total += ambient + diffuse + specular;
	}

	gl_FragColor = total;
}*/

const int NUM_LIGHTS = 1;

uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 lightVector[NUM_LIGHTS];	// L
uniform vec3 eyeSpaceLightVector[NUM_LIGHTS];
varying vec3 fragNormal;	// N
varying vec3 eyeSpaceVertex;

void main()
{
	vec4 total = vec4(0, 0, 0, 0);
	vec3 eyeVecNormal = normalize(-eyeSpaceVertex);	// E
	float lightingFactor;
	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		lightingFactor = max(dot(lightVector[i], fragNormal), 0.0);

		vec4 diffuse = diffuseColor[i] * lightingFactor;
		diffuse = clamp(diffuse, 0.0, 1.0);

		vec3 reflectVec = normalize(-reflect(lightVector[i], fragNormal)); // R
		vec4 specularColor = min(diffuseColor[i] + 0.5, 1);
		vec4 specular = specularColor * pow(max(dot(reflectVec, eyeVecNormal), 0.0), 0.3 * 5.0f);	//Este vale
		specular = clamp(specular, 0.0, 1.0);

		total += vec4(0.1, 0.1, 0.1, 1) + diffuse + specular;
	}

	gl_FragColor = total;
}
