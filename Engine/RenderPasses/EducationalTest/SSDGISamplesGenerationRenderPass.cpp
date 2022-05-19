#include "SSDGISamplesGenerationRenderPass.h"

SSDGISamplesGenerationRenderPass::SSDGISamplesGenerationRenderPass () :
	_ssdgiSamplesVolume (nullptr)
{

}

void SSDGISamplesGenerationRenderPass::Init (const RenderSettings& settings)
{
	/*
	 * Create screen space directional occlusion samples volume
	*/

	_ssdgiSamplesVolume = new SSDGISamplesVolume (settings.ssdgi_sample_count);
}

RenderVolumeCollection* SSDGISamplesGenerationRenderPass::Execute (const RenderScene* renderScene, const Camera* camera,
	const RenderSettings& settings, RenderVolumeCollection* rvc)
{
	/*
	 * Update screen space directional occlusion samples volume
	*/

	UpdateSamplesVolume (settings);

	return rvc->Insert ("SSDGISamplesVolume", _ssdgiSamplesVolume);
}

bool SSDGISamplesGenerationRenderPass::IsAvailable (const RenderScene* renderScenee, const Camera* camera,
	const RenderSettings& settings, const RenderVolumeCollection* rvc) const
{
	/*
	 * Always execute screen space directional occlusion samples generation render pass
	*/

	return settings.indirect_diffuse_enabled;
}

void SSDGISamplesGenerationRenderPass::Clear ()
{
	/*
	 * Clear screen space directional occlusion samples volume
	*/

	delete _ssdgiSamplesVolume;
}

void SSDGISamplesGenerationRenderPass::UpdateSamplesVolume (const RenderSettings& settings)
{
	if (_ssdgiSamplesVolume->GetSamplesCount () != settings.ssdgi_sample_count) {

		/*
		 * Clear screen space ambient occlusion samples volume
		*/

		delete _ssdgiSamplesVolume;

		/*
		 * Create screen space ambient occlusion samples volume
		*/

		_ssdgiSamplesVolume = new SSDGISamplesVolume (settings.ssdgi_sample_count);
	}
}
