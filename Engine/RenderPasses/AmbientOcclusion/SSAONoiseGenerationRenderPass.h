#ifndef SSAONOISEGENERATIONRENDERPASS_H
#define SSAONOISEGENERATIONRENDERPASS_H

#include "RenderPasses/NoiseMap/NoiseGenerationRenderPass.h"

class SSAONoiseGenerationRenderPass : public NoiseGenerationRenderPass
{
public:
	bool IsAvailable (const RenderScene* renderScene, const Camera* camera,
		const RenderSettings& settings, const RenderVolumeCollection* rvc) const;
protected:
	glm::ivec2 GetNoiseMapVolumeResolution (const RenderSettings& settings) const;
};

#endif