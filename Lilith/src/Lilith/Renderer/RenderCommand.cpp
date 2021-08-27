#include "lipch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Lilith {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}