#version 330

layout(location = 0) out vec3 out_color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 viewProjectionMatrix;
uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat3 normalWorldMatrix;
uniform mat4 inverseViewMatrix;
uniform mat3 inverseNormalWorldMatrix;

uniform vec3 cameraPosition;

uniform sampler3D volumeTextureR;
uniform sampler3D volumeTextureG;
uniform sampler3D volumeTextureB;
uniform vec3 minVertex;
uniform vec3 maxVertex;
uniform ivec3 volumeSize;

uniform int lpvRefractiveIterations;
uniform float lpvIndirectRefractiveIntensity;

#include "deferred.glsl"

float GetInterpolatedComp (float comp, float minValue, float maxValue)
{
	return ((comp - minValue) / (maxValue - minValue));
}

vec3 GetPositionInVolume (vec3 origin)
{
	vec3 positionInVolume;

	positionInVolume.x = GetInterpolatedComp (origin.x, minVertex.x, maxVertex.x);
	positionInVolume.y = GetInterpolatedComp (origin.y, minVertex.y, maxVertex.y);
	positionInVolume.z = GetInterpolatedComp (origin.z, minVertex.z, maxVertex.z);

	return positionInVolume;
}

/*Spherical harmonics coefficients - precomputed*/
#define SH_C0 0.282094792f // 1 / 2sqrt(pi)
#define SH_C1 0.488602512f // sqrt(3/pi) / 2
#define PI 3.1415926f

vec4 evalSH_direct( vec3 direction ) {	
	return vec4( SH_C0, -SH_C1 * direction.y, SH_C1 * direction.z, -SH_C1 * direction.x );
}

/*
 * Subsurface Scattering Calculation
*/

vec3 CalcIndirectRefractiveLight (vec3 in_position, vec3 in_normal, float in_refractiveIndex)
{
	// Compute fragment world position and world normal
	vec3 worldSpacePos = vec3 (inverseViewMatrix * vec4 (in_position, 1.0));
	vec3 worldSpaceNormal = normalMatrix * inverseNormalWorldMatrix * in_normal;

	vec3 eyeToFragment = normalize (worldSpacePos - cameraPosition);
	vec3 refractiveDir = refract (eyeToFragment, worldSpaceNormal, 1.0 / in_refractiveIndex);

	vec4 SHintensity = evalSH_direct( -refractiveDir );

	vec3 refractiveStep = 1.0f / volumeSize * refractiveDir * 1.732;
	vec3 volumePos = GetPositionInVolume (worldSpacePos);

	vec3 subsurfaceScatteringColor = vec3 (0.0f);

	for(float refractiveIndex = 0; refractiveIndex < lpvRefractiveIterations; refractiveIndex++) {

		vec3 indirectColor = vec3( 
			dot( SHintensity, texture( volumeTextureR, volumePos) ),
			dot( SHintensity, texture( volumeTextureG, volumePos ) ),
			dot( SHintensity, texture( volumeTextureB, volumePos ) )
		);

		subsurfaceScatteringColor += max (indirectColor, 0.0) / PI / 5;

		volumePos += refractiveStep;
	}

	return clamp (subsurfaceScatteringColor * lpvIndirectRefractiveIntensity, 0.0, 1.0);
}

void main()
{
	vec2 texCoord = CalcTexCoord();
	vec3 in_position = textureLod (gPositionMap, texCoord, 0).xyz;
	vec3 in_normal = textureLod (gNormalMap, texCoord, 0).xyz;
	float in_transparency = textureLod (gDiffuseMap, texCoord, 0).w;
	float in_refractiveIndex = textureLod (gNormalMap, texCoord, 0).w;

	in_normal = normalize(in_normal);

	out_color = vec3 (0.0);

	if (in_transparency > 0.0) {
		out_color = CalcIndirectRefractiveLight (in_position, in_normal, in_refractiveIndex);
	}
}
