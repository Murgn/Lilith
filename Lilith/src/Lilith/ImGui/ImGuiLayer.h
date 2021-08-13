#pragma once

#include "Lilith/Layer.h"

#include "Lilith/Events/ApplicationEvent.h"
#include "Lilith/Events/KeyEvent.h"
#include "Lilith/Events/MouseEvent.h"

namespace Lilith {

	class LILITH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}
