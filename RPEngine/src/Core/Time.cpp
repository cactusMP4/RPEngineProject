#include "Time.h"

namespace rpe {
	TimeStep Time::GetTime() {
		return TimeStep(static_cast<float>(glfwGetTime()));
	}
}