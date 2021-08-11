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
		LI_INFO("ExampleLayer::Update");
	}

	void OnEvent(Lilith::Event& event) override
	{
		LI_TRACE("{0}", event);
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