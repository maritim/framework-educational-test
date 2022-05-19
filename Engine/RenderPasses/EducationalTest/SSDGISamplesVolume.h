#ifndef SSDGISAMPLESVOLUME_H
#define SSDGISAMPLESVOLUME_H

#include "Renderer/RenderVolumeI.h"

#include <glm/vec3.hpp>

struct SSDGISamples
{
	int sampleCount;
	int sampleCountPadding [3];
	glm::vec4 samples [500];
};

class ENGINE_API SSDGISamplesVolume : public RenderVolumeI
{
protected:
	SSDGISamples _samples;
	unsigned int _samplesUBO;

	std::vector<PipelineAttribute> _attributes;

public:
	SSDGISamplesVolume (std::size_t sampleCount);
	~SSDGISamplesVolume ();

	const std::vector<PipelineAttribute>& GetCustomAttributes () const;

	std::size_t GetSamplesCount () const;
};

#endif
