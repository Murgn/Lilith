#pragma once

#include "Core.h"

#include "Window.h"
#include "Lilith/LayerStack.h"
#include "Lilith/Events/Event.h"
#include "Lilith/Events/ApplicationEvent.h"

#include "Lilith/ImGui//ImGuiLayer.h"

#include "Lilith/Renderer/Shader.h"
#include "Lilith/Renderer/Buffer.h"

namespace Lilith {

	class LILITH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr <VertexBuffer> m_VertexBuffer;
		std::unique_ptr <IndexBuffer> m_IndexBuffer;

	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}