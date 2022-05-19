#ifndef EDUCATIONALTESTRENDERMODULE_H
#define EDUCATIONALTESTRENDERMODULE_H

#include "Renderer/RenderModule.h"

#include "Renderer/RenderModuleManager.h"

class EducationalTestRenderModule : public RenderModule
{
protected:
	void Init ();
};

REGISTER_RENDER_MODULE(EducationalTestRenderModule)

#endif