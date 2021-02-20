#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	
	m_PreviousState = m_CurrentState;
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			std::cout ;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}


void dae::InputManager::ButtonCommand(ControllerButton button) const
{
	std::unique_ptr<Command> command;
	if (GetKeyState(button) == KeyState::Pressed)
	{
		switch (button)
		{
		case ControllerButton::ButtonA:
			command = std::make_unique<JumpCommand>();

			break;
		case ControllerButton::ButtonB:
			command = std::make_unique<FartCommand>();
			break;
		case ControllerButton::ButtonX:
			command = std::make_unique<FireCommand>();
			break;
		case ControllerButton::ButtonY:
			command = std::make_unique<DuckCommand>();
			break;
		case ControllerButton::RightShoulder:
			std::cout << "RightShoulder was pressed\n";
			break;
		case ControllerButton::LeftShoulder:
			std::cout << "LeftShoulder was pressed\n";
			break;
		case ControllerButton::RightThumb:
			std::cout << "RightThumb was pressed\n";
			break;
		case ControllerButton::LeftThumb:
			std::cout << "LeftThumb was pressed\n";
			break;
		case ControllerButton::Back:
			std::cout << "Back was pressed\n";
			break;
		case ControllerButton::Start:
			std::cout << "Start was pressed\n";
			break;
		case ControllerButton::RightDPad:
			std::cout << "RightDPad was pressed\n";
			break;
		case ControllerButton::LeftDPad:
			std::cout << "LeftDPad was pressed\n";
			break;
		case ControllerButton::DownDPad:
			std::cout << "DownDPad was pressed\n";
			break;
		case ControllerButton::UpDPad:
			std::cout << "UpDPad was pressed\n";
			break;
		case ControllerButton::LeftTrigger:
			std::cout << "LeftTrigger was pressed: " << int(m_CurrentState.Gamepad.bLeftTrigger) << std::endl;
			break;
		case ControllerButton::RightTrigger:
			std::cout << "RightTrigger was pressed: " << int(m_CurrentState.Gamepad.bRightTrigger) << std::endl;
			break;
		case ControllerButton::LeftThumbStick:
			std::cout << "LeftThumbStick was used : " << int(m_CurrentState.Gamepad.sThumbLX) << " - " << int(m_CurrentState.Gamepad.sThumbLY) << std::endl;
			break;
		case ControllerButton::RightThumbStick:
			std::cout << "RightThumbStick was used : " << int(m_CurrentState.Gamepad.sThumbRX) << " - " << int(m_CurrentState.Gamepad.sThumbRY) << std::endl;
			break;
		default: break;
		}
	}
	if (command != nullptr)
	{
		command->Execute();
	}
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	return Pressed(button, m_CurrentState);
}

bool dae::InputManager::WasPressed(ControllerButton button) const
{

	return Pressed(button, m_PreviousState);
}

bool dae::InputManager::Pressed(ControllerButton button, const XINPUT_STATE& keystate) const
{

	int buttonValue = int(button);
	switch (button)
	{
	case ControllerButton::ButtonA:
	case ControllerButton::ButtonB:
	case ControllerButton::ButtonX:
	case ControllerButton::ButtonY:
	case ControllerButton::RightShoulder:
	case ControllerButton::LeftShoulder:
	case ControllerButton::RightThumb:
	case ControllerButton::LeftThumb:
	case ControllerButton::Back:
	case ControllerButton::Start:
	case ControllerButton::RightDPad:
	case ControllerButton::LeftDPad:
	case ControllerButton::DownDPad:
	case ControllerButton::UpDPad:
		if (keystate.Gamepad.wButtons == buttonValue && keystate.Gamepad.wButtons != 0)
			return true;
		break;
	case ControllerButton::LeftTrigger:
		if (keystate.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			return true;
		break;
	case ControllerButton::RightTrigger:
		if (keystate.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
			return true;
		break;
	case ControllerButton::LeftThumbStick:
		if (keystate.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && keystate.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			if (keystate.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && keystate.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		return true;
		break;
	case ControllerButton::RightThumbStick:
		if (keystate.Gamepad.sThumbRX < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && keystate.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		{
			if (keystate.Gamepad.sThumbRY < XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && keystate.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		return true;
		break;
	default:
		return false;
	}



	return false;

}

dae::KeyState dae::InputManager::GetKeyState(ControllerButton button) const
{
	if (WasPressed(button))
	{
		if (IsPressed(button))
		{
			return KeyState::Held;
		}
		return KeyState::Released;
	}
	else
	{
		if (IsPressed(button))
		{
			return KeyState::Pressed;
		}
		return KeyState::Idle;
	}
}


