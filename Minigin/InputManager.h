#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"

namespace dae
{
	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000,
		RightShoulder = 0x0200,
		LeftShoulder = 0x0100,
		RightThumb = 0x0080,
		LeftThumb = 0x0040,
		Back = 0x0020,
		Start = 0x0010,
		RightDPad = 0x0008,
		LeftDPad = 0x0004,
		DownDPad = 0x0002,
		UpDPad = 0x0001,
		LeftTrigger = 0x8001,
		RightTrigger = 0x8002,
		LeftThumbStick = 0x8003,
		RightThumbStick = 0x8004,

		
	};

	enum class KeyState
	{
		Idle, Pressed, Held, Released
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void ButtonCommand(ControllerButton button) const;

		bool IsPressed(ControllerButton button) const;
		bool WasPressed(ControllerButton button) const;
		bool Pressed(ControllerButton button, const XINPUT_STATE& keystate) const;
		KeyState GetKeyState(ControllerButton) const;
	private:
		XINPUT_STATE m_CurrentState{}, m_PreviousState{};
		




	};

}
