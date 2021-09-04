#pragma once

#ifdef LI_PLATFORM_WINDOWS

extern Lilith::Application* Lilith::CreateApplication();

int main(int argc, char** argv)
{
	Lilith::Log::Init();
	
	LI_PROFILE_BEGIN_SESSION("Startup", "LilithProfile-Startup.json");
	auto app = Lilith::CreateApplication();
	LI_PROFILE_END_SESSION();

	LI_PROFILE_BEGIN_SESSION("Runtime", "LilithProfile-Runtime.json");
	app->Run();
	LI_PROFILE_END_SESSION();

	LI_PROFILE_BEGIN_SESSION("Shutdown", "LilithProfile-Shutdown.json");
	delete app;
	LI_PROFILE_END_SESSION();
}

#endif
