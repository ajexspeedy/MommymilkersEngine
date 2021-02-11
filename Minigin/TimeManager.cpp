#include "MiniginPCH.h"
#include "TimeManager.h"

float dae::TimeManager::GetDeltaTime()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	float deltaTime = std::chrono::duration<float>(m_CurrentTime - m_LastTime).count();
	m_LastTime = m_CurrentTime;
	return deltaTime;
}
