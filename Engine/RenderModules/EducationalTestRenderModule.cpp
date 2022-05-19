#include "EducationalTestRenderModule.h"

#include "RenderPasses/ResultFrameBufferGenerationRenderPass.h"
#include "RenderPasses/DeferredGeometryRenderPass.h"
#include "RenderPasses/DeferredSkyboxRenderPass.h"
#include "RenderPasses/DeferredBlitRenderPass.h"
#include "RenderPasses/ForwardRenderPass.h"
#include "RenderPasses/GUI/GUIGizmosRenderPass.h"
#include "RenderPasses/GUI/GUIRenderPass.h"
#include "RenderPasses/WindowBlitRenderPass.h"

#include "RenderPasses/Container/ContainerRenderPass.h"
#include "RenderPasses/IterateOverRenderVolumeCollection.h"

#include "RenderPasses/ScreenSpaceDirectionalOcclusion/SSDOSamplesGenerationRenderPass.h"
#include "RenderPasses/ScreenSpaceDirectionalOcclusion/SSDOInterpolatedRenderPass.h"
#include "RenderPasses/ScreenSpaceDirectionalOcclusion/SSDORenderPass.h"
#include "RenderPasses/ScreenSpaceDirectionalOcclusion/SSDOShadowRenderPass.h"
#include "RenderPasses/ScreenSpaceDirectionalOcclusion/SSDOTemporalFilterRenderPass.h"
#include "RenderPasses/ScreenSpaceDirectionalOcclusion/SSDOAccumulationRenderPass.h"

#include "RenderPasses/ShadowMap/DirectionalLightShadowMapRenderPass.h"
#include "RenderPasses/DeferredDirectionalLightRenderPass.h"
#include "RenderPasses/ScreenSpaceDirectionalOcclusion/SSDODirectionalLightRenderPass.h"

#include "RenderPasses/ScreenSpaceAmbientOcclusion/SSAOSamplesGenerationRenderPass.h"
#include "RenderPasses/ScreenSpaceAmbientOcclusion/SSAONoiseGenerationRenderPass.h"
#include "RenderPasses/ScreenSpaceAmbientOcclusion/SSAORenderPass.h"
#include "RenderPasses/ScreenSpaceAmbientOcclusion/SSAOBlurRenderPass.h"

#include "RenderPasses/AmbientLight/AmbientLightRenderPass.h"

#include "RenderPasses/FramebufferMipmapsGenerationRenderPass.h"

#include "RenderPasses/DirectionalLightContainerRenderVolumeCollection.h"

#include "RenderPasses/DeferredPointLightRenderPass.h"
#include "RenderPasses/PointLightContainerRenderVolumeCollection.h"

#include "RenderPasses/IdleRenderPass.h"
#include "RenderPasses/ScreenSpaceReflections/SSRRenderPass.h"
#include "RenderPasses/ScreenSpaceReflections/SSRSpecularRenderPass.h"
#include "RenderPasses/ScreenSpaceReflections/SSRAccumulationRenderPass.h"
#include "RenderPasses/ScreenSpaceSubsurfaceScattering/SSSubsurfaceScatteringRenderPass.h"
#include "RenderPasses/ScreenSpaceSubsurfaceScattering/SSSubsurfaceScatteringAccumulationRenderPass.h"
#include "RenderPasses/TemporalAntialiasing/TAARenderPass.h"
#include "RenderPasses/Bloom/BrightExtractionRenderPass.h"
#include "RenderPasses/Bloom/BloomHorizontalBlurRenderPass.h"
#include "RenderPasses/Bloom/BloomVerticalBlurRenderPass.h"
#include "RenderPasses/Bloom/BloomAccumulationRenderPass.h"
#include "RenderPasses/HighDynamicRange/HDRRenderPass.h"
#include "RenderPasses/TextureLUT/TextureLUTRenderPass.h"
#include "RenderPasses/GammaCorrection/GammaCorrectionRenderPass.h"

#include "RenderPasses/EducationalTest/SSDGISamplesGenerationRenderPass.h"
#include "RenderPasses/EducationalTest/SSDGIRenderPass.h"
#include "RenderPasses/EducationalTest/Internal/SSDGIAccumulationRenderPass.h"
#include "RenderPasses/EducationalTest/SSReflectionsRenderPass.h"
#include "RenderPasses/EducationalTest/Internal/SSReflectionsAccumulationRenderPass.h"

void EducationalTestRenderModule::Init ()
{
	_renderPasses.push_back (new ResultFrameBufferGenerationRenderPass ());

	/*
	 * Deferred GBuffers generation
	*/

	_renderPasses.push_back (new DeferredGeometryRenderPass ());

	/*
	 * Ambient light internal pass
	*/

	_renderPasses.push_back (new AmbientLightRenderPass ());

	/*
	 * A sequence of passes
	*/

	_renderPasses.push_back (ContainerRenderPass::Builder ()

		/*
		 * Iteration through directional lights
		*/

		.Volume (new DirectionalLightContainerRenderVolumeCollection ())

		/*
		 * Generation of the depth buffer from the light perspective
		*/

		.Attach (new DirectionalLightShadowMapRenderPass ())

		/*
		 * Direct illumination is computed 
		*/

		.Attach (new DeferredDirectionalLightRenderPass ())

		.Build ());

	/*
	 * Skybox render
	*/

	_renderPasses.push_back (new DeferredSkyboxRenderPass ());

	/*
	 * Post processing passes
	*/

	_renderPasses.push_back (ContainerRenderPass::Builder ()

		/*
		 * Iterate once through the pass sequence that follows
		*/

		.Volume (new IterateOverRenderVolumeCollection (1))

		/*
		 * Internal pass
		*/

		.Attach (new IdleRenderPass ())

		/*
		 * A sequence of passes
		*/

		.Attach (ContainerRenderPass::Builder ()

			/*
			 * Iterate once through the pass sequence that follows
			*/

			.Volume (new IterateOverRenderVolumeCollection (1))

			/*
			 * Generation of samples for screen space diffuse indirect
			 * illumination
			 * 
			 * TODO: Complete the task in "SSDGISamplesVolume.cpp"
			 * The samples volume is already managed in the following
			 * render pass, only the generation of the samples is required.
			*/

			.Attach (new SSDGISamplesGenerationRenderPass ())

			/*
			 * Screen space diffuse indirect illumination computation
			 *
			 * TODO: Complete the tasks in "SSDGIRenderPass.cpp" and "ssdgiFragment.glsl"
			*/

			.Attach (new SSDGIRenderPass ())

			/*
			 * Accumulation pass
			 *
			 * TODO: Complete the tasks in "SSDGIAccumulationRenderPass.cpp"
			*/

			.Attach (new SSDGIAccumulationRenderPass ())
			.Build ())

		/*
		 * A sequence of passes
		*/

		.Attach (ContainerRenderPass::Builder ()

			/*
			 * Iterate once through the pass sequence that follows
			*/

			.Volume (new IterateOverRenderVolumeCollection (1))

			/*
			 * Screen space reflections computation
			 *
			 * TODO: Complete the tasks in "ssrFragment.glsl"
			*/

			.Attach (new SSReflectionsRenderPass ())

			/*
			 * Accumulation pass
			*/

			.Attach (new SSReflectionsAccumulationRenderPass ())
			.Build ())

		/*
		 * Built-in post processing passes
		*/

		.Attach	(new TAARenderPass ())
		.Attach (ContainerRenderPass::Builder ()
			.Volume (new IterateOverRenderVolumeCollection (1))
			.Attach (new BrightExtractionRenderPass ())
			.Attach (ContainerRenderPass::Builder ()
				.Volume (new IterateOverRenderVolumeCollection (5))
				.Attach (new BloomHorizontalBlurRenderPass ())
				.Attach (new BloomVerticalBlurRenderPass ())
				.Build ())
			.Attach (new BloomAccumulationRenderPass ())
			.Build ())
		.Attach (new HDRRenderPass ())
		.Attach (new TextureLUTRenderPass ())
		.Attach (new GammaCorrectionRenderPass ())
		.Attach (new DeferredBlitRenderPass ())
		.Build ());
	_renderPasses.push_back (new ForwardRenderPass ());
	_renderPasses.push_back (new GUIGizmosRenderPass ());
}
