#include <Lilith.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

		Lilith::Ref<Lilith::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Lilith::VertexBuffer::Create(vertices, sizeof(vertices)));
		Lilith::BufferLayout layout = {
			{Lilith::ShaderDataType::Float3, "a_Position"},
			{Lilith::ShaderDataType::Float4, "a_Color"}
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Lilith::Ref<Lilith::IndexBuffer> indexBuffer;
		indexBuffer.reset(Lilith::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Lilith::VertexArray::Create());

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,

		};

		Lilith::Ref<Lilith::VertexBuffer> squareVB;
		squareVB.reset(Lilith::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{Lilith::ShaderDataType::Float3, "a_Position"},
			{Lilith::ShaderDataType::Float2, "a_TexCoord"}
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Lilith::Ref<Lilith::IndexBuffer> squareIB;
		squareIB.reset(Lilith::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_ShaderLibrary.Load("assets/shaders/Default.glsl");
		m_ShaderLibrary.Load("assets/shaders/Color.glsl");
		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_CheckerboardTexture = Lilith::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LilithLogoTexture = Lilith::Texture2D::Create("assets/textures/Lilith Logo.png");

		std::dynamic_pointer_cast<Lilith::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Lilith::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
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
			auto defaultShader = m_ShaderLibrary.Get("Default");
			auto colorShader = m_ShaderLibrary.Get("Color");
			auto textureShader = m_ShaderLibrary.Get("Texture");

			m_CheckerboardTexture->Bind();
			Lilith::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
			m_LilithLogoTexture->Bind();
			Lilith::Renderer::Submit(textureShader, m_SquareVA);

			Lilith::Renderer::Submit(defaultShader, m_SquareVA,
				glm::translate(glm::mat4(1.0f), glm::vec3(0.6f))
				* glm::scale(glm::mat4(1.0f), glm::vec3(0.4f)));

			std::dynamic_pointer_cast<Lilith::OpenGLShader>(colorShader)->Bind();
			std::dynamic_pointer_cast<Lilith::OpenGLShader>(colorShader)->UploadUniformFloat3("u_Color", m_SquareColor);
			Lilith::Renderer::Submit(colorShader, m_SquareVA,
				glm::translate(glm::mat4(1.0f), glm::vec3(-0.6f))
				* glm::scale(glm::mat4(1.0f), glm::vec3(0.4f)));

			// Triangle
			// Lilith::Renderer::Submit(m_DefaultShader, m_VertexArray);
		}

		Lilith::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("LILITH ENGINE");
		ImGui::Text("USE ARROW KEYS TO MOVE CAMERA, A & D TO ROTATE CAMERA.");
		ImGui::Separator();
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
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
	Lilith::ShaderLibrary m_ShaderLibrary;

	Lilith::Ref<Lilith::VertexArray> m_VertexArray;
	Lilith::Ref<Lilith::VertexArray> m_SquareVA;

	Lilith::Ref<Lilith::Texture2D> m_CheckerboardTexture, m_LilithLogoTexture;

	Lilith::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 2.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquarePosition;

	glm::vec3 m_SquareColor = { 0.2f, 0.5f, 1.0f };
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