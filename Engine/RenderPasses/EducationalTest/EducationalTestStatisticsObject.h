#ifndef EDUCATIONALTESTSTATISTICSOBJECT_H
#define EDUCATIONALTESTSTATISTICSOBJECT_H

#include "Debug/Statistics/StatisticsObject.h"

#include "RenderPasses/FramebufferRenderVolume.h"

struct ENGINE_API EducationalTestStatisticsObject : public StatisticsObject
{
	DECLARE_STATISTICS_OBJECT(EducationalTestStatisticsObject)

	FramebufferRenderVolume* ssdgiMapVolume;
	FramebufferRenderVolume* ssrMapVolume;
};

#endif