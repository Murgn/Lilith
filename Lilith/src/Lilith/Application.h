#pragma once

#include "Core.h"

namespace Lilith {

	class LILITH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}