#pragma once

#include "Lilith/Core/Layer.h"

#include "Lilith/Events/ApplicationEvent.h"
#include "Lilith/Events/KeyEvent.h"
#include "Lilith/Events/MouseEvent.h"

namespace Lilith {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
