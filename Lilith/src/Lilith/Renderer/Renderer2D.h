#pragma once

#include "OrthographicCamera.h"

#include "Texture.h"

namespace Lilith {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives	---------------------------------

		//		-- DrawQuad w/ color
		static void DrawQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4 color);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4 color);
		//		-- DrawQuad w/ texture
		static void DrawQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const Ref<Texture2D>& texture);
		//		-- DrawQuad w/ color + texture
		static void DrawQuad(const glm::vec2& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4 color, const Ref<Texture2D>& texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec3& rotation, const glm::vec2& size, const glm::vec4 color, const Ref<Texture2D>& texture);
	};

}
