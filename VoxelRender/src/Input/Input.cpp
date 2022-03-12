#include "Input.h"

namespace InputSystem
{
	uint8_t Input::s_JoysticksCount = 0;
	double Input::s_XMousePos = 0;
	double Input::s_XMouseOffset = 0;

	double Input::s_YMousePos = 0;
	double Input::s_YMouseOffset = 0;

	double Input::s_ScrollOffset = 0;
	double Input::s_CurrentScroll = 0;

	bool Input::s_Keys[512];
	bool Input::s_MouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
	bool Input::s_Joysticks[GLFW_JOYSTICK_LAST + 1];
	char Input::s_GamepadButtons[GLFW_GAMEPAD_BUTTON_LAST + 1];
	float Input::s_GamepadAxis[GLFW_GAMEPAD_AXIS_LAST + 1];

	bool Input::IsKeyPressed(uint32_t key) 
	{ 
		return s_Keys[key]; 
	}

	bool Input::IsMouseButtonPress(uint32_t button) 
	{ 
		return s_MouseButtons[button]; 
	}

	double Input::GetXMousePos() 
	{ 
		return s_XMousePos; 
	}

	double Input::GetXOffset() 
	{ 
		double xoffset = s_XMouseOffset;
		s_XMouseOffset = 0;
		return xoffset;
	}

	double Input::GetYMousePos() 
	{ 
		return s_YMousePos; 
	}

	double Input::GetYOffset() 
	{ 
		double yoffset = s_YMouseOffset;
		s_YMouseOffset = 0;
		return yoffset;
	}

	double Input::GetYMouseScrollOffset() 
	{ 
		double yoffset = s_ScrollOffset; 
		s_ScrollOffset = 0; 
		return yoffset; 
	}

	void Input::SetKeyPressed(uint32_t key, bool flag) 
	{ 
		s_Keys[key] = flag; 
	}

	void Input::SetMouseButtonPressed(uint32_t button, bool flag) 
	{ 
		s_MouseButtons[button] = flag;
	}

	void Input::SetXMousePosition(double xpos) 
	{
		s_XMouseOffset = xpos - s_XMousePos;
		s_XMousePos = xpos; 
	}

	void Input::SetYMousePosition(double ypos) 
	{ 
		s_YMouseOffset = s_YMousePos - ypos;
		s_YMousePos = ypos;
	}

	void Input::SetYMouseScrollOffset(double yoffset) 
	{ 
		s_ScrollOffset = s_CurrentScroll - yoffset; 
		s_CurrentScroll = yoffset;
	}

	void Input::UpdateGamepadStates()
	{
		for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++)
		{
			GLFWgamepadstate state;
			if (glfwGetGamepadState(i, &state))
			{
				memcpy(s_GamepadButtons, state.buttons, sizeof(s_GamepadButtons) * sizeof(s_GamepadButtons[0]));
				memcpy(s_GamepadAxis, state.axes, sizeof(s_GamepadAxis) * sizeof(s_GamepadAxis[0]));
			}
		}
	}
}