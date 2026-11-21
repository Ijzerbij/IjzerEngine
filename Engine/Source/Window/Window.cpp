#include "Window/Window.hpp"

#include <iostream>

namespace Eng
{
	namespace GLFW // GLFW global window functions
	{
		std::string glfwErrorString()
		{
			const char* desc = nullptr;
			int code = glfwGetError(&desc);
			return "GLFW error " + std::to_string(code) + ": " + (desc ? desc : "unknown");
		}
	}

	Window::Window()
	{
		std::cout << "window started" << std::endl;

		m_window = nullptr;
		m_instance = VK_NULL_HANDLE;
		m_surface = VK_NULL_HANDLE;
		m_resized = false;
		m_ownsGlfwRef = false;
	}

	Window::~Window()
	{
	}
}