#include "ImGui/ImGuiLayer.h"

#include "imgui.h"
#include "ImGui/ImGuiRenderer.h"
#include "Application.h"

namespace rpe {
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {};
	ImGuiLayer::~ImGuiLayer() {};


	void ImGuiLayer::Attach() {
		RPE_CORE_INFO("Attaching ImGui layer");

		ImGui::CreateContext();
		ImGui::StyleColorsClassic();

		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::Detach() {

	}

	void ImGuiLayer::Update() {
		ImGuiIO& io = ImGui::GetIO();

		const Application& app = Application::GetApplication();

		io.DisplaySize = ImVec2(
			static_cast<float>(app.GetWindow().GetWidth()),
			static_cast<float>(app.GetWindow().GetHeight())
		);

		const double time = glfwGetTime();
		io.DeltaTime = static_cast<float>(layerTime > 0.0f ? (time - layerTime) : (1.0f / 60.0f));
		layerTime = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) {
		
	}
}