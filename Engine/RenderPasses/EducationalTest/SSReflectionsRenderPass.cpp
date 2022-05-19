#include "SSReflectionsRenderPass.h"

#include "Debug/Statistics/StatisticsManager.h"
#include "EducationalTestStatisticsObject.h"

bool SSReflectionsRenderPass::IsAvailable (const RenderScene* renderScene, const Camera* camera,
	const RenderSettings& settings, const RenderVolumeCollection* rvc) const
{
	/*
	 * Check if screen space reflection is enabled
	*/

	return settings.indirect_specular_enabled;
}

std::string SSReflectionsRenderPass::GetPostProcessFragmentShaderPath () const
{
	return "Assets/Shaders/EducationalTest/ssrFragment.glsl";
}

std::string SSReflectionsRenderPass::GetPostProcessVolumeName () const
{
	return "SSRMapVolume";
}

glm::ivec2 SSReflectionsRenderPass::GetPostProcessVolumeResolution (const RenderSettings& settings) const
{
	return glm::ivec2 (settings.resolution.width, settings.resolution.height);
}

FramebufferRenderVolume* SSReflectionsRenderPass::CreatePostProcessVolume (const RenderSettings& settings) const
{
	/*
	 * Create screen space reflections framebuffer
	*/

	Resource<Texture> texture = Resource<Texture> (new Texture ("reflectionMap"));

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

	auto ssrStatisticsObject = StatisticsManager::Instance ()->GetStatisticsObject <EducationalTestStatisticsObject> ();

	ssrStatisticsObject->ssrMapVolume = renderVolume;

	return renderVolume;
}

std::vector<PipelineAttribute> SSReflectionsRenderPass::GetCustomAttributes (const Camera* camera,
	const RenderSettings& settings, RenderVolumeCollection* rvc)
{
	/*
	 * Attach post process volume attributes to pipeline
	*/

	std::vector<PipelineAttribute> attributes = PostProcessRenderPass::GetCustomAttributes (camera, settings, rvc);

	/*
	 * Attach screen space ambient occlusion attributes to pipeline
	*/

	PipelineAttribute ssrIterationCount;
	PipelineAttribute ssrIterationStep;
	PipelineAttribute ssrThickness;

	ssrIterationCount.type = PipelineAttribute::AttrType::ATTR_1I;
	ssrIterationStep.type = PipelineAttribute::AttrType::ATTR_1F;
	ssrThickness.type = PipelineAttribute::AttrType::ATTR_1F;

	ssrIterationCount.name = "ssrIterationCount";
	ssrIterationStep.name = "ssrIterationStep";
	ssrThickness.name = "ssrThickness";

	ssrIterationCount.value.x = settings.ssr_iteration_count;
	ssrIterationStep.value.x = settings.ssr_iteration_step;
	ssrThickness.value.x = settings.ssr_sample_thickness;

	attributes.push_back (ssrIterationCount);
	attributes.push_back (ssrIterationStep);
	attributes.push_back (ssrThickness);

	return attributes;
}
