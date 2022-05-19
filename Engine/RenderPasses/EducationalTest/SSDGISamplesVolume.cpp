#ifdef _MSC_VER
	#define _USE_MATH_DEFINES
#endif

#include "SSDGISamplesVolume.h"

#include <cstring>

#include "Core/Random/Random.h"

#include "Wrappers/OpenGL/GL.h"

SSDGISamplesVolume::SSDGISamplesVolume (std::size_t sampleCount) :
	_samplesUBO (0)
{
	/*
	 * Initialize sample count
	*/

	_samples.sampleCount = sampleCount;

	/*
	 * Initialize samples
	*/

	for (std::size_t index = 0; index < sampleCount; index++) {

		/*
		 * TODO: Generate random sampling points in 
		 * interval [-1, 1] for all components {x, y}
		 *
		 * In order to obtain good visual results for the
		 * diffuse indirect illumination, the samples must
		 * be in a disk of radius 1.
		 * Maybe use the normalization of the sample.
		 *
		 * The sample is 2D, but we used glm::vec4 because of
		 * the GPU memory requirements.
		 * Only {x, y} are required to be generated.
		*/

		_samples.samples [index] = glm::vec4 (0.0f);
	}

	/*
	 * Store the buffer in GPU memory
	*/

	GL::GenBuffers (1, &_samplesUBO);
	GL::BindBuffer (GL_UNIFORM_BUFFER, _samplesUBO);
	GL::BufferData (GL_UNIFORM_BUFFER, sizeof (float) * 501 * 4, &_samples, GL_STATIC_DRAW);
	GL::BindBuffer (GL_UNIFORM_BUFFER, 0);

	/*
	 * Create attributes
	*/

	PipelineAttribute ssdgiSamples;

	ssdgiSamples.type = PipelineAttribute::AttrType::ATTR_BLOCK;

	ssdgiSamples.name = "ssdgiSamples";

	ssdgiSamples.value.x = _samplesUBO;

	_attributes.push_back (ssdgiSamples);
}

SSDGISamplesVolume::~SSDGISamplesVolume ()
{
	GL::DeleteBuffers (1, &_samplesUBO);
}

const std::vector<PipelineAttribute>& SSDGISamplesVolume::GetCustomAttributes () const
{
	return _attributes;
}

std::size_t SSDGISamplesVolume::GetSamplesCount () const
{
	return _samples.sampleCount;
}
