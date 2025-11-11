#include "Camera.h"

namespace rpe {
	Camera::Camera(
		const float fov,
		const float viewDistance,
		const CameraProjection perspective
	) : FOV(fov), viewDistance(viewDistance), projection(perspective) {
		const Window& window = Application::GetApplication().GetWindow();
		aspectRatio = static_cast<float>(window.GetWidth()) / static_cast<float>(window.GetHeight());
	}

	void Camera::SetFov(const float fov) {FOV = fov;}
	void Camera::SetAspectRatio(const float ar) { aspectRatio = ar; }
	void Camera::SetViewDistance(const float distance) { viewDistance = distance; }
	void Camera::SetProjection(const CameraProjection proj) { projection = proj; }

	Transform& Camera::GetTransform() { return transform; }

	float Camera::GetFov() const { return FOV; }
	float Camera::GetAspectRatio() const { return aspectRatio; }
	float Camera::GetViewDistance() const { return viewDistance; }
	CameraProjection Camera::GetProjection() const { return projection; }

	glm::mat4 Camera::GetViewMatrix() const {
		return glm::lookAt(transform.GetPosition(), transform.GetPosition() + transform.GetLookDir(), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	glm::mat4 Camera::GetProjectionMatrix() const {
		switch (projection) {
		case CameraProjection::Orthographic:
			return glm::ortho(-1.0f, 1.0f, -1.0f / aspectRatio, 1.0f / aspectRatio, 0.0f, viewDistance);
		case CameraProjection::Perspective:
			return glm::perspective(glm::radians(FOV), aspectRatio, 0.1f, viewDistance);
		}
		RPE_CORE_ERROR("Unknown projection type!");
		return { 1.0f };
	}
	glm::mat4 Camera::GetViewProjMatrix() const {
		return GetProjectionMatrix() * GetViewMatrix();
	}
}