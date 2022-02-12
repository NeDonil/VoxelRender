#pragma once

#include <iostream>
#include <string>
#include <GLFW/glfw3.h>

namespace GraphicsSystem
{
	class Window
	{
	public:
		Window(uint32_t width, uint32_t height, const std::string& title, bool fullscreen = false);
		~Window() = default;

		void Resize(uint32_t width, uint32_t height);

		bool IsActive();
		void SetWindowActive(bool flag);

		void SetTitle(const std::string& title);
		std::string& GetTitle();

		void SetFullScreen(bool flag);
		void SetVSync(bool flag);

		float GetTimestep() { return m_Timestep; }

		void Update();
		void Close();

		GLFWwindow* GetWindow();
		uint32_t GetWidth();
		uint32_t GetHeight();

	private:
		float m_Timestep;
		float m_LastFrame;

		uint32_t m_Width;
		uint32_t m_Height;

		std::string m_Title;

		GLFWwindow* m_Window;
	};

}