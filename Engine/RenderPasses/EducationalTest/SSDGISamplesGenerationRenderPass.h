#ifndef SSDGISAMPLESGENERATIONRENDERPASS_H
#define SSDGISAMPLESGENERATIONRENDERPASS_H

#include "RenderPasses/Container/ContainerRenderSubPassI.h"

#include "SSDGISamplesVolume.h"

class ENGINE_API SSDGISamplesGenerationRenderPass : public ContainerRenderSubPassI
{
	DECLARE_RENDER_PASS(SSDGISamplesGenerationRenderPass)

protected:
	SSDGISamplesVolume* _ssdgiSamplesVolume;

public:
	SSDGISamplesGenerationRenderPass ();

	virtual void Init (const RenderSettings& settings);
	RenderVolumeCollection* Execute (const RenderScene* renderScene, const Camera* camera,
		const RenderSettings& settings, RenderVolumeCollection* rvc);

	bool IsAvailable (const RenderScene* renderScene, const Camera* camera,
		const RenderSettings& settings, const RenderVolumeCollection* rvc) const;

	void Clear ();
protected:
	void UpdateSamplesVolume (const RenderSettings& settings);
};

#endif
