#include <Lilith.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Lilith::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_SquarePosition(0.0f)
	{
		m_VertexArray.reset(Lilith::VertexArray::Create());

		// Positions
		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Lilith::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lilith::VertexBuffer::Create(vertices, sizeof(vertices)));
		Lilith::BufferLayout layout = {
			{Lilith::ShaderDataType::Float3, "a_Position"},
			{Lilith::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Lilith::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lilith::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Lilith::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,

		};

		std::shared_ptr<Lilith::VertexBuffer> squareVB;
		squareVB.reset(Lilith::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Lilith::ShaderDataType::Float3, "a_Position"},
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Lilith::IndexBuffer> squareIB;
		squareIB.reset(Lilith::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
		
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Lilith::Shader(vertexSource, fragmentSource));

		std::string vertexSource2 = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSource2 = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;
		
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader2.reset(new Lilith::Shader(vertexSource2, fragmentSource2));
	}

	void OnUpdate(Lilith::DeltaTime deltaTime) override
	{

		// Camera Movement ------------------------------------------------
		if (Lilith::Input::IsKeyPressed(LI_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaTime;
		if (Lilith::Input::IsKeyPressed(LI_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * deltaTime;
		if (Lilith::Input::IsKeyPressed(LI_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * deltaTime;
		if (Lilith::Input::IsKeyPressed(LI_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaTime;

		// Camera Rotation ------------------------------------------------
		if (Lilith::Input::IsKeyPressed(LI_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * deltaTime;
		if (Lilith::Input::IsKeyPressed(LI_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

		Lilith::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.11f, 1.0f });
		Lilith::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Lilith::Renderer::BeginScene(m_Camera);

		{
			static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

			for (int x = -5; x < 6; x++)
			{
				for (int y = -5; y < 6; y++)
				{
					glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
					glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
					Lilith::Renderer::Submit(m_Shader2, m_SquareVA, transform);
				}

			}

			Lilith::Renderer::Submit(m_Shader, m_VertexArray);
		}

		Lilith::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("LILITH ENGINE");
		ImGui::Text("USE ARROW KEYS TO MOVE CAMERA, A & D TO ROTATE CAMERA.");
		ImGui::End();
	}

	void OnEvent(Lilith::Event& event) override
	{
		Lilith::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Lilith::KeyPressedEvent>(LI_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Lilith::KeyPressedEvent& event)
	{
		//LI_INFO("Key Pressed");
		return 0;
	}

private:
	std::shared_ptr<Lilith::Shader> m_Shader;
	std::shared_ptr<Lilith::VertexArray> m_VertexArray;

	std::shared_ptr<Lilith::Shader> m_Shader2;
	std::shared_ptr<Lilith::VertexArray> m_SquareVA;

	Lilith::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquarePosition;
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