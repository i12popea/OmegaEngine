/* Fragment shader */

const int NUM_LIGHTS = 1;

uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 lightVector[NUM_LIGHTS];
varying vec3 eyeSpaceVertex;
uniform vec3 eyeSpaceLightVector[NUM_LIGHTS];
uniform sampler2D color_texture;
uniform sampler2D normal_texture;

void main()
{
	vec4 color = vec4(0, 0, 0, 0);
	vec3 eyeVecNormal = normalize(-eyeSpaceVertex);
	// Extract the normal from the normal map
	vec3 normal = normalize(texture2D(normal_texture, gl_TexCoord[0].st).rgb * 2.0 - 1.0);

	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		// Determine where the light is positioned (this can be set however you like)
		vec3 light_pos = normalize(eyeSpaceLightVector[i]);

		// Calculate the lighting diffuse value
		float diffuse = max(dot(normal, light_pos), 0.0);

		vec3 reflectVec = normalize(-reflect(lightVector[i], normal));
		vec4 specularColor = min(diffuseColor[i] + 0.5, 1);
		vec4 specular = specularColor * pow(max(dot(reflectVec, eyeVecNormal), 0.0), 32.0f);
		specular = clamp(specular, 0.0, 1.0);

	//	color += vec4(diffuse * texture2D(color_texture, gl_TexCoord[0].st).rgb + texture2D(color_texture, gl_TexCoord[0].st).rgb * 0.1, 1.0) + specular;
		color += vec4(diffuse * texture2D(color_texture, gl_TexCoord[0].st).rgb, 1.0) + specular;
	}

	// Set the output color of our current pixel
	gl_FragColor = color;
}
