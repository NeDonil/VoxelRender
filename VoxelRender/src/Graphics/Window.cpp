#include "Window.h"
#include <cassert>
#include <GLAD/glad.h>

#include <Input/Input.h>
#include "Renderer.h"

namespace GraphicsSystem
{

	Window::Window(uint32_t width, uint32_t height, const std::string& title, bool fullscreen)
		: m_Width(width), m_Height(height), m_Title(title), m_Timestep(0)
	{
		assert(glfwInit());
		GLFWmonitor* monitor = nullptr;
		
		if (fullscreen)
			monitor = glfwGetPrimaryMonitor();

		m_Window = glfwCreateWindow(width, height, title.c_str(), monitor, nullptr);
		m_LastFrame = glfwGetTime();

		glfwSetCursorPos(m_Window, width / 2, height / 2);
		glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		InputSystem::Input::SetXMousePosition(width / 2);
		InputSystem::Input::SetYMousePosition(height / 2);

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods){		
				if (action == GLFW_PRESS)
					InputSystem::Input::SetKeyPressed(key, true);
				else if (action == GLFW_RELEASE)
					InputSystem::Input::SetKeyPressed(key, false);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow * window, double xpos, double ypos){
				InputSystem::Input::SetXMousePosition(xpos);
				InputSystem::Input::SetYMousePosition(ypos);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods){
				if (action == GLFW_PRESS)
					InputSystem::Input::SetMouseButtonPressed(button, true);
				else if(action == GLFW_RELEASE)
					InputSystem::Input::SetMouseButtonPressed(button, false);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset){
				InputSystem::Input::SetYMouseScrollOffset(yoffset);
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height){
				Renderer::SetViewport(0, 0, width, height);
		});

		glfwSetJoystickCallback([](int jid, int event) {
			if (event == GLFW_CONNECTED)
			{
				InputSystem::Input::JoystickConnected(jid);
			}

			else if (event == GLFW_DISCONNECTED)
			{
				InputSystem::Input::JoystickDisconnected(jid);
			}

		});

		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwMakeContextCurrent(m_Window);
		
		assert(gladLoadGL());
	}

	void Window::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
	}

	void Window::Resize(uint32_t width, uint32_t height)
	{
		glfwSetWindowSize(m_Window, width, height);
	}

	bool Window::IsActive()
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void Window::SetWindowActive(bool flag)
	{
		glfwSetWindowShouldClose(m_Window, !flag);
	}

	void Window::SetFullScreen(bool flag)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		if (flag)
		{
			glfwSetWindowMonitor(m_Window, glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);
		}

		else
		{
			glfwSetWindowMonitor(m_Window, nullptr, 100, 100, m_Width, m_Height, mode->refreshRate);
		}
	}

	void Window::SetVSync(bool flag)
	{
		glfwSwapInterval(flag);
	}

	void Window::Update()
	{
		float currentTime = glfwGetTime();
		m_Timestep = currentTime - m_LastFrame;
		m_LastFrame = currentTime;

		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void Window::Close()
	{
		glfwDestroyWindow(m_Window);
	}

	GLFWwindow* Window::GetWindow()
	{
		return m_Window;
	}

	uint32_t Window::GetWidth()
	{
		return m_Width;
	}

	uint32_t Window::GetHeight()
	{
		return m_Height;
	}

	std::string& Window::GetTitle()
	{
		return m_Title;
	}
}
