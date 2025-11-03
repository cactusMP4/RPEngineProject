#pragma once

#include "../Core/Core.h"
#include "../Core/Layer.h"

namespace rpe {
	class RPE_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();


		void Attach() override;
		void Detach() override;
		void RenderImGui(TimeStep dt) override;

		void Begin();
		void End();
	private:
		double layerTime = 0.0f;
	};
}