#pragma once

#ifdef LI_PLATFORM_WINDOWS

extern Lilith::Application* Lilith::CreateApplication();

int main(int argc, char** argv)
{
	Lilith::Log::Init();
	

	auto app = Lilith::CreateApplication();
	app->Run();
	delete app;
}

#endif
