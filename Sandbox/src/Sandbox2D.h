#pragma once

#include <Lilith.h>

class Sandbox2D : public Lilith::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() {}

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Lilith::DeltaTime deltaTime) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Lilith::Event& e) override;
private:
	Lilith::OrthographicCameraController m_CameraController;

	// Temporary
	Lilith::Ref<Lilith::VertexArray> m_SquareVA;
	Lilith::Ref<Lilith::Shader> m_Shader;

	Lilith::Ref<Lilith::Texture2D> m_Texture;

	glm::vec3 m_Rotation = { 0.0f, 0.0f, 45.0f };

	glm::vec4 m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };

};