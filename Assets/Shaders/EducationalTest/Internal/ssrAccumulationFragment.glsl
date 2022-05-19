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

uniform float ssrIntensity;

uniform sampler2D postProcessMap;

uniform sampler2D reflectionMap;

#include "deferred.glsl"

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

void main()
{
	vec2 texCoord = CalcTexCoord();
	vec3 in_position = textureLod (gPositionMap, texCoord, 0).xyz;
	vec3 in_normal = textureLod (gNormalMap, texCoord, 0).xyz;
	vec3 in_diffuse = texture (postProcessMap, texCoord).xyz;
	vec3 in_specular = textureLod (gSpecularMap, texCoord, 0).xyz;
	vec3 in_reflection = textureLod (reflectionMap, texCoord, 0).xyz;

	in_normal = normalize (in_normal);

	vec3 reflection = vec3 (0.0f);

	if (length (in_reflection) > 0.0f) {
		reflection = in_reflection;
	}

	vec3 reflectionDirection = normalize (reflect (normalize (in_position), in_normal));

	vec3 fresnel = fresnelSchlick(max(dot(in_normal, normalize(-in_position)), 0.0), vec3 (0.0f));

	out_color = in_diffuse + (in_specular * reflection *
		clamp (-reflectionDirection.z, 0.0f, 1.0f) *
		fresnel * ssrIntensity);
}
