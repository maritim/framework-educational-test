#version 330 core

layout(location = 0) out vec3 out_color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat3 normalWorldMatrix;

uniform vec3 cameraPosition;

uniform float ssdgiIntensity;
uniform float ssdgiSamplingRadius;

uniform sampler2D postProcessMap;

#include "deferred.glsl"

layout(std140) uniform ssdgiSamples
{
	int ssdgiSampleCount;
	vec2 ssdgiSample[500];
};

vec3 CalcDebug (vec2 texcoord)
{
	float aspectRatio = screenSize.x / screenSize.y;

	for (int sampleIndex = 0; sampleIndex < ssdgiSampleCount; ++ sampleIndex) {
		vec2 sample = vec2 (0.5f) + ssdgiSample [sampleIndex].xy * ssdgiSamplingRadius;

		if (distance (vec2 (texcoord.x * aspectRatio, texcoord.y), sample) < 0.01) {
			return vec3 (1, 0, 0);
		}
	}

	return vec3 (0.0f);
}

vec3 CalcDiffuseIndirectIllumination (vec3 fragmentViewSpacePosition,
	vec3 fragmentViewSpaceNormal, vec2 fragmentScreenSpacePosition)
{
	vec3 diffuseIndirectIllumination = vec3 (0.0f);

	/*
	 * Iterate through sampling points
	*/

	for (int sampleIndex = 0; sampleIndex < ssdgiSampleCount; ++ sampleIndex) {

		/*
		 * Get sample
		*/

		vec2 sample = ssdgiSample [sampleIndex];

		/*
		 * TODO: Compute a scaled sample, so that it is transformed [-1, 1]
		 * interval in [-ssdgiSamplingRadius, ssdgiSamplingRadius]
		*/

		vec2 scaledSample = vec2 (0.0f);

		/*
		 * TODO: Center the scaled sample around the position of the fragment
		 * in screen space
		*/

		vec2 sampleScreenSpacePos = vec2 (0.0f);

		/*
		 * Check sample to be inside the screen
		*/

		bvec2 a = greaterThan(sampleScreenSpacePos, vec2(1.0, 1.0));
		bvec2 b = lessThan(sampleScreenSpacePos, vec2(0.0, 0.0));

		if (any(bvec2(any(a), any(b)))) {
			continue;
		}

		/*
		 * Get sample position, normal vector direct illumination
		*/

		vec3 vplPos = textureLod (gPositionMap, sampleScreenSpacePos, 3).xyz;
		vec3 vplNormal = textureLod (gNormalMap, sampleScreenSpacePos, 3).xyz;
		vec3 vplDirectIllumination = textureLod (postProcessMap, sampleScreenSpacePos, 3).xyz;

		vplNormal = normalize (vplNormal);

		/*
		 * Compute the parameters required by the diffuse
		 * indirect lighting computations
		*/

		vec3 dir = normalize (fragmentViewSpacePosition - vplPos);

		float viewSpaceDist = distance (fragmentViewSpacePosition, vplPos);
		float screenSpaceDist = distance (fragmentScreenSpacePosition, sampleScreenSpacePos.xy);

		/*
		 * TODO: Compute diffuse indirect illumination according to the formula
		*/

		vec3 vplDiffuseIndirectIllumination = vec3 (0.0f);

		diffuseIndirectIllumination += vplDiffuseIndirectIllumination;
	}

	/*
	 * TODO: Weight the diffuse indirect illumination with 1 / ssdgiSampleCount
	*/

	diffuseIndirectIllumination /= 1;

	return max (diffuseIndirectIllumination, vec3 (0.0)) * ssdgiIntensity;
}

void main()
{
	vec2 texCoord = CalcTexCoord();
	vec3 in_position = texture (gPositionMap, texCoord).xyz;
	vec3 in_normal = texture (gNormalMap, texCoord).xyz;

	in_normal = normalize(in_normal);

	out_color = CalcDiffuseIndirectIllumination (in_position, in_normal, texCoord);

	/*
	 * TODO: Remove the debug draw. This draws the set of samples as a set of
	 * red dots on the screen for debug purposes. Remove it and let only the
	 * computation of the diffuse indirect illumination to be executed
	*/

	out_color = CalcDebug (texCoord);
}
