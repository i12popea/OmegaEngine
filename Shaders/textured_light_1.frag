// Fragment Shader

uniform sampler2D color_texture;

const int NUM_LIGHTS = 2;

uniform vec4 diffuseColor[NUM_LIGHTS];
varying vec3 lightVector[NUM_LIGHTS];
varying vec3 fragNormal;
varying vec3 eyeSpaceVertex;

void main()
{
	vec4 total = vec4(0, 0, 0, 0);
	vec3 eyeVecNormal = normalize(-eyeSpaceVertex);
	for(int i = 0; i < NUM_LIGHTS; i++)
	{
		vec3 ct, cf;
		vec4 texel;
		float lightingFactor, at, af;
		lightingFactor = max(dot(lightVector[i], fragNormal), 0.0);

		vec3 reflectVec = normalize(-reflect(lightVector[i], fragNormal));
		vec4 specularColor = min(diffuseColor[i] + 0.5, 1);
		vec4 specular = specularColor * pow(max(dot(reflectVec, eyeVecNormal), 0.0), 32.0f);
		specular = clamp(specular, 0.0, 1.0);

		cf = lightingFactor * vec3(diffuseColor[i]) * gl_FrontMaterial.ambient.rgb + gl_FrontMaterial.diffuse.rgb + gl_FrontMaterial.specular.rgb;
		af = gl_FrontMaterial.diffuse.a;
		texel = texture2D(color_texture, gl_TexCoord[0].st);
		ct = texel.rgb;
		at = texel.a;

		total += vec4(ct * cf, at * af) + specular;
	}

	gl_FragColor = total;
}
