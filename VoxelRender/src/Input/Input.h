#pragma once

#include <Graphics/Window.h>
#include <cstdint>
#include <functional>

namespace InputSystem
{
	class Input
	{
	public:
		friend class GraphicsSystem::Window;

		Input() = default;
		~Input() = default;

		static bool IsKeyPressed(uint32_t key);
		static bool IsMouseButtonPress(uint32_t button);

		static double GetXMousePos();
		static double GetXOffset();

		static double GetYMousePos();
		static double GetYOffset();

		static double GetYMouseScrollOffset();

		static float GetGamepadButton(int button) { return s_GamepadButtons[button]; }
		static float GetGamepadAxis(int axis) { return s_GamepadAxis[axis]; }
		static void UpdateGamepadStates();
	private:
		static void SetKeyPressed(uint32_t key, bool flag);
		static void SetMouseButtonPressed(uint32_t button, bool flag);

		static void SetXMousePosition(double xpos);
		static void SetYMousePosition(double ypos);

		static void SetYMouseScrollOffset(double yoffset);

		static void JoystickConnected(int id) { s_JoysticksCount++; s_Joysticks[id] = true; }
		static void JoystickDisconnected(int id) { s_JoysticksCount--; s_Joysticks[id] = false; }
	private:
		static double s_XMousePos;
		static double s_XMouseOffset;

		static double s_YMousePos;
		static double s_YMouseOffset;

		static double s_CurrentScroll;
		static double s_ScrollOffset;

		static uint8_t s_JoysticksCount;
		static bool s_Joysticks[GLFW_JOYSTICK_LAST + 1];
		static bool s_Keys[512];
		static bool s_MouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
		static char s_GamepadButtons[GLFW_GAMEPAD_BUTTON_LAST + 1];
		static float s_GamepadAxis[GLFW_GAMEPAD_AXIS_LAST + 1];
	};
}