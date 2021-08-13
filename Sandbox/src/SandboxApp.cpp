#include <Lilith.h>

class ExampleLayer : public Lilith::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Lilith::Input::IsKeyPressed(LI_KEY_A))
			LI_TRACE("YABA DABA DOOOOOO");
	}

	void OnEvent(Lilith::Event& event) override
	{
		//LI_TRACE("{0}", event);
	}
};

class Sandbox : public Lilith::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Lilith::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Lilith::Application* Lilith::CreateApplication()
{
	return new Sandbox();
}