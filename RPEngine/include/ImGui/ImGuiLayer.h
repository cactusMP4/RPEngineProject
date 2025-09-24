#pragma once

#include "Core.h"
#include "Layer.h"

namespace rpe {
	class RPE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void Attach() override;
		void Detach() override;
		void RenderImGui() override;

		void Begin();
		void End();
	private:
		double layerTime = 0.0f;
	};
}