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
		double layerTime = 0.0f;
	};
}