#pragma once

#include "Core.h"
#include "TimeStep.h"
#include <GLFW/glfw3.h>

namespace rpe {
	class RPE_API Time {
	public:
		static TimeStep GetTime();
	};
}