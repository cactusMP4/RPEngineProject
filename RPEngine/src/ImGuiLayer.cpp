#include "ImGui/ImGuiLayer.h"

#include "imgui.h"
#include "ImGui/ImGuiRenderer.h"
#include "GLFW/glfw3.h"

namespace rpe {
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {};
	ImGuiLayer::~ImGuiLayer() {};


	void ImGuiLayer::Attach() {
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
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		ImGuiIO& io = ImGui::GetIO();

		float time = glfwGetTime();
		io.DeltaTime = layerTime > 0.0f ? (time - layerTime) : (1.0f / 60.0f);
		layerTime = time;

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event) {
		
	}
}