#include "Application.h"

#include "Lilith/Events/ApplicationEvent.h"
#include "Lilith/Log.h"

#include <iostream>

namespace Lilith {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		LI_TRACE(e);

		while (true);
	}

}