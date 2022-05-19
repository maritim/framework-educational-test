#include "SSDGIRenderPass.h"

#include "Wrappers/OpenGL/GL.h"

#include "Debug/Statistics/StatisticsManager.h"
#include "EducationalTestStatisticsObject.h"

#include "Utils/Extensions/MathExtend.h"

bool SSDGIRenderPass::IsAvailable (const RenderScene* renderScene, const Camera* camera,
	const RenderSettings& settings, const RenderVolumeCollection* rvc) const
{
	/*
	 * TODO: Execute the pass only when diffuse indirect illumination
	 * is active.
	 *
	 * HINT: Use settings.
	*/

	return true;
}

std::string SSDGIRenderPass::GetPostProcessFragmentShaderPath () const
{
	return "Assets/Shaders/EducationalTest/ssdgiFragment.glsl";
}

std::string SSDGIRenderPass::GetPostProcessVolumeName () const
{
	return "SSDGIMapVolume";
}

glm::ivec2 SSDGIRenderPass::GetPostProcessVolumeResolution (const RenderSettings& settings) const
{
	/*
	 * TODO: Set the resolution of the viewport.
	 * The resolution of 500^2 is a dummy value.
	 *
	 * Hint: Use settings.resolution
	*/

	return glm::ivec2 (500);
}

FramebufferRenderVolume* SSDGIRenderPass::CreatePostProcessVolume (const RenderSettings& settings) const
{
	/*
	 * Create screen space directional occlusion framebuffer
	*/

	Resource<Texture> texture = Resource<Texture> (new Texture ("ssdgiMap"));

	glm::ivec2 size = GetPostProcessVolumeResolution (settings);

	texture->SetSize (Size (size.x, size.y));
	texture->SetMipmapGeneration (false);
	texture->SetSizedInternalFormat (TEXTURE_SIZED_INTERNAL_FORMAT::FORMAT_RGB16);
	texture->SetInternalFormat (TEXTURE_INTERNAL_FORMAT::FORMAT_RGB);
	texture->SetChannelType (TEXTURE_CHANNEL_TYPE::CHANNEL_FLOAT);
	texture->SetWrapMode (TEXTURE_WRAP_MODE::WRAP_CLAMP_EDGE);
	texture->SetMinFilter (TEXTURE_FILTER_MODE::FILTER_NEAREST);
	texture->SetMagFilter (TEXTURE_FILTER_MODE::FILTER_NEAREST);
	texture->SetAnisotropicFiltering (false);

	Resource<Framebuffer> framebuffer = Resource<Framebuffer> (new Framebuffer (texture));

	FramebufferRenderVolume* renderVolume = new FramebufferRenderVolume (framebuffer);

	/*
	 * Update statistics object
	*/

	auto ssdgiStatisticsObject = StatisticsManager::Instance ()->GetStatisticsObject <EducationalTestStatisticsObject> ();

	ssdgiStatisticsObject->ssdgiMapVolume = renderVolume;

	return renderVolume;
}

std::vector<PipelineAttribute> SSDGIRenderPass::GetCustomAttributes (const Camera* camera,
	const RenderSettings& settings, RenderVolumeCollection* rvc)
{
	/*
	 * Attach post process volume attributes to pipeline
	*/

	std::vector<PipelineAttribute> attributes = PostProcessRenderPass::GetCustomAttributes (camera, settings, rvc);

	/*
	 * Attach screen space directional occlusion attributes to pipeline
	*/

	PipelineAttribute ssdgiIntensity;
	PipelineAttribute ssdgiSamplingRadius;

	ssdgiIntensity.type = PipelineAttribute::AttrType::ATTR_1F;
	ssdgiSamplingRadius.type = PipelineAttribute::AttrType::ATTR_1F;

	ssdgiIntensity.name = "ssdgiIntensity";
	ssdgiSamplingRadius.name = "ssdgiSamplingRadius";

	ssdgiIntensity.value.x = settings.ssdgi_intensity;
	ssdgiSamplingRadius.value.x = settings.ssdgi_sampling_radius;

	attributes.push_back (ssdgiIntensity);
	attributes.push_back (ssdgiSamplingRadius);

	return attributes;
}
