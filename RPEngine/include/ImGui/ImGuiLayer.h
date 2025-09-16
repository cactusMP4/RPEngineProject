#pragma once

#include "Layer.h"

namespace rpe {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void Attach();
		void Detach();
		void Update();
		void OnEvent(Event& event);
	private:
		float layerTime = 0.0f;
	};
}