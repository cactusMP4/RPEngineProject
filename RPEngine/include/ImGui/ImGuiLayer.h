#pragma once

#include "Core.h"
#include "Layer.h"

namespace rpe {
	class RPE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void Attach();
		void Detach();
		void Update();
		void OnEvent(Event& event);

	private:
		bool OnMouseMovedEvent(const MouseMovedEvent& event);
		bool OnMouseButtonPressedEvent(const MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(const MouseButtonReleasedEvent& event);
		bool OnMouseScrolledEvent(const MouseScrolledEvent& event);

		bool OnKeyPressedEvent(const KeyPressedEvent& event);
		bool OnKeyReleasedEvent(const KeyReleasedEvent& event);
		bool OnKeyTypedEvent(const KeyTypedEvent& event);

		bool OnWindowResizeEvent(const WindowResizeEvent& event);


		double layerTime = 0.0f;
	};
}