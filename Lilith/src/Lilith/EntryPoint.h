#pragma once

#ifdef LI_PLATFORM_WINDOWS

extern Lilith::Application* Lilith::CreateApplication();

int main(int argc, char** argv)
{
	Lilith::Log::Init();
	LI_CORE_TRACE("CORE TRACE!");
	LI_CORE_INFO("CORE INFO!");
	LI_CORE_WARN("CORE WARN!");
	LI_CORE_ERROR("CORE ERROR!");
	LI_CORE_CRITICAL("CORE CRITICAL!");

	LI_TRACE("APP TRACE!");
	LI_INFO("APP INFO!");
	LI_WARN("APP WARN!");
	LI_ERROR("APP ERROR!");
	LI_CRITICAL("APP CRITICAL!");

	auto app = Lilith::CreateApplication();
	app->Run();
	delete app;
}

#endif
