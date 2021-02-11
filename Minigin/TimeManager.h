#pragma once
#include <chrono>
#include "Singleton.h"

namespace dae
{

	class TimeManager : public Singleton<TimeManager>
	{
	public:

		float GetDeltaTime();
	
	private:
		friend class Singleton<TimeManager>;
		TimeManager() = default;

		using clock = std::chrono::steady_clock::time_point;
		clock m_LastTime = std::chrono::high_resolution_clock::now(); // default value
		clock m_CurrentTime = {};
		
		
	};
}
