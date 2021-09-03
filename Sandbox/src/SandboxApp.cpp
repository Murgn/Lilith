#include <Lilith.h>
#include <Lilith/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Lilith::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		m_VertexArray = Lilith::VertexArray::Create();

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

		m_SquareVA = Lilith::VertexArray::Create();

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

		/* visual studio shouts at me if i dont give the shaders references :(
		you dont need references though, visual will just be mean if you dont use them */
		Lilith::Ref<Lilith::Shader> defaultShader = m_ShaderLibrary.Load("assets/shaders/Default.glsl");
		Lilith::Ref<Lilith::Shader> colorShader = m_ShaderLibrary.Load("assets/shaders/Color.glsl");
		Lilith::Ref<Lilith::Shader> textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_CheckerboardTexture = Lilith::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LilithLogoTexture = Lilith::Texture2D::Create("assets/textures/Lilith Logo.png");

		std::dynamic_pointer_cast<Lilith::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Lilith::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Lilith::DeltaTime deltaTime) override
	{
		// Update
		m_CameraController.OnUpdate(deltaTime);

		// Render 
		Lilith::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.11f, 1.0f });
		Lilith::RenderCommand::Clear();

		Lilith::Renderer::BeginScene(m_CameraController.GetCamera());
		{
			Lilith::Ref<Lilith::Shader> defaultShader = m_ShaderLibrary.Get("Default");
			Lilith::Ref<Lilith::Shader> colorShader = m_ShaderLibrary.Get("Color");
			Lilith::Ref<Lilith::Shader> textureShader = m_ShaderLibrary.Get("Texture");

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
		/*ImGui::Begin("LILITH ENGINE");
		ImGui::Text("USE ARROW KEYS TO MOVE CAMERA, A & D TO ROTATE CAMERA.");
		ImGui::Separator();
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();*/
	}

	void OnEvent(Lilith::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Lilith::ShaderLibrary m_ShaderLibrary;

	Lilith::Ref<Lilith::VertexArray> m_VertexArray;
	Lilith::Ref<Lilith::VertexArray> m_SquareVA;

	Lilith::Ref<Lilith::Texture2D> m_CheckerboardTexture, m_LilithLogoTexture;

	Lilith::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.5f, 1.0f };
};

class Sandbox : public Lilith::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
		//new Lilith::DiscordRPC();
	}

	~Sandbox()
	{

	}
};

Lilith::Application* Lilith::CreateApplication()
{
	return new Sandbox();
}