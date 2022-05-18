uniform sampler2D subsurfaceScatteringMap;

uniform int subsurfaceScatteringEnabled;

vec3 CalcSubsurfaceScatteringLight ()
{
	vec3 in_subsurfaceScattering = vec3 (0.0f);

	if (subsurfaceScatteringEnabled == 1) {
		vec2 texCoord = CalcTexCoord();

		in_subsurfaceScattering = texture2D (subsurfaceScatteringMap, texCoord).xyz;
	}

	return in_subsurfaceScattering;
}
