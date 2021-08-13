#include <Lilith.h>

#include "imgui/imgui.h"

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

	void OnImGuiRender() override
	{
		ImGui::Begin("Murgn Land");
		ImGui::Text("yo stupid\n no im not\n whats 9+10\n21");
		ImGui::End();
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
	}

	~Sandbox()
	{

	}
};

Lilith::Application* Lilith::CreateApplication()
{
	return new Sandbox();
}