#ifndef TAARENDERPASS_H
#define TAARENDERPASS_H

#include "RenderPasses/TemporalFiltering/TemporalFilterRenderPass.h"

class ENGINE_API TAARenderPass : public TemporalFilterRenderPass
{
	DECLARE_RENDER_PASS(TAARenderPass)

public:
	bool IsAvailable (const RenderScene* renderScene, const Camera* camera,
		const RenderSettings& settings, const RenderVolumeCollection* rvc) const;

	std::string GetPostProcessFragmentShaderPath () const;
	FramebufferRenderVolume* CreatePostProcessVolume (const RenderSettings& settings) const;
};

#endif