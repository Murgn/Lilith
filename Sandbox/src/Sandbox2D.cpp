#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	LI_PROFILE_FUNCTION();

	m_Texture = Lilith::Texture2D::Create("assets/textures/Lilith Logo.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Lilith::DeltaTime deltaTime)
{
	LI_PROFILE_FUNCTION();

	// NOTE: Update
	m_CameraController.OnUpdate(deltaTime);

	// NOTE: Render Preperation
	{
		LI_PROFILE_SCOPE("Renderer Preperation");
		Lilith::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.11f, 1.0f });
		Lilith::RenderCommand::Clear();
	}
	
	// NOTE: Render Draw
	{
		LI_PROFILE_SCOPE("Renderer Draw");
		Lilith::Renderer2D::BeginScene(m_CameraController.GetCamera());
		{
			Lilith::Renderer2D::DrawQuad({ 0.0f, 0.5f }, m_Rotation, { 0.5f, 0.5f }, { 0.75f, 0.15f, 0.15f, 1.0f }, m_Texture);
			Lilith::Renderer2D::DrawQuad({ -1.0f, 0.0f }, m_Rotation, { 0.5f, 0.5f }, { 0.15f, 0.75f, 0.15f, 1.0f }, m_Texture);
			Lilith::Renderer2D::DrawQuad({ 1.0f, 0.0f }, m_Rotation, { 0.5f, 0.5f }, { 0.15f, 0.15f, 0.75f, 1.0f }, m_Texture);
			Lilith::Renderer2D::DrawQuad({ 0.0f, -0.5f }, m_Rotation, { 0.5f, 0.5f }, m_Color, m_Texture);
		}
		Lilith::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	LI_PROFILE_FUNCTION();
	ImGui::Begin("2D Sandbox");
	ImGui::Text("Move with WASD, rotate with Q & E, scroll to zoom.");
	ImGui::Separator();
	ImGui::ColorEdit4("Color:", glm::value_ptr(m_Color));
	ImGui::SliderFloat3("Rotation:", glm::value_ptr(m_Rotation), -360, 360);

	ImGui::End();
}

void Sandbox2D::OnEvent(Lilith::Event& e)
{
	m_CameraController.OnEvent(e);
}