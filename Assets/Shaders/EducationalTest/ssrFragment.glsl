#version 330 core

layout(location = 0) out vec3 out_color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat3 normalWorldMatrix;
uniform mat4 inverseViewMatrix;

uniform vec3 cameraPosition;
uniform vec2 cameraZLimits;

uniform int ssrIterationCount;
uniform float ssrIterationStep;
uniform float ssrThickness;

uniform sampler2D postProcessMap;

#include "deferred.glsl"

vec3 CalcScreenSpaceReflection (vec3 fragmentViewSpacePosition,
	vec3 fragmentViewSpaceNormal, vec2 fragmentScreenSpacePosition)
{
	/*
	 * Compute view direction
	*/

	vec3 viewDirection = fragmentViewSpacePosition;

	/*
	 * Compute reflection direction
	*/

	vec3 reflectionDirection = reflect (viewDirection, fragmentViewSpaceNormal);
	reflectionDirection = normalize (reflectionDirection);

	/*
	 * Iterate through
	*/

	for (int index = 1; index <= ssrIterationCount; index ++) {

		/*
		 * TODO: Compute the reflection direction after "index" times
		 * segments of size ssrIterationStep.
		*/

		vec3 segmentedReflectionDirection = vec3 (0.0f);

		/*
		 * TODO: Compute the sample view space position along the
		 * segmented reflection direction computed before. The reflection
		 * direction starts in fragmentViewSpacePosition
		*/

		vec3 sampleViewSpacePosition = vec3 (0.0f);

		/*
		 * Discard reflections beyond camera z
		*/

		if (sampleViewSpacePosition.z <= -cameraZLimits.y) {
			return vec3 (0.0f);
		}

		/*
		 * Compute screen space position of the sample
		*/

		vec4 sampleScreenSpacePos = projectionMatrix * vec4 (sampleViewSpacePosition, 1.0f);
		sampleScreenSpacePos /= sampleScreenSpacePos.w;
		sampleScreenSpacePos.xyz = sampleScreenSpacePos.xyz * 0.5f + 0.5f;

		/*
		 * Check sample to be inside the screen
		*/

		bvec2 a = greaterThan(sampleScreenSpacePos.xy, vec2(1.0, 1.0));
		bvec2 b = lessThan(sampleScreenSpacePos.xy, vec2(0.0, 0.0));

		if (any(bvec2(any(a), any(b)))) {
			return vec3 (0.0f);
		}

		/*
		 * Check intersection with the geometry visible on the screen
		*/

		vec3 sampleCheckViewSpacePosition = texture (gPositionMap, sampleScreenSpacePos.xy).xyz;

		if (sampleViewSpacePosition.z > sampleCheckViewSpacePosition.z - ssrThickness) {
			continue;
		}

		vec3 sampleColor = texture (postProcessMap, sampleScreenSpacePos.xy).xyz;

		return sampleColor;
	}

	return vec3 (0.0f);
}

void main()
{
	vec2 texCoord = CalcTexCoord();
	vec3 in_position = texture (gPositionMap, texCoord).xyz;
	vec3 in_normal = texture (gNormalMap, texCoord).xyz;
	vec3 in_specular = texture (gSpecularMap, texCoord).xyz;

	in_normal = normalize(in_normal);

	out_color = CalcScreenSpaceReflection (in_position, in_normal, texCoord);
}
