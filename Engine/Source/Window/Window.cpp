#include "Window/Window.hpp"

#include "Core/Logging.hpp"

#include <iostream>

namespace Eng
{
	namespace GLFW // GLFW global window functions
	{
		void glfwErrorString()
		{
			const char* desc = nullptr;
			int code = glfwGetError(&desc);
			std::string error = "GLFW error " + std::to_string(code) + ": " + (desc ? desc : "unknown");
			std::cout << error << std::endl;
			Eng::logger::LogCritticalError(Eng::logger::window, 0);
			return;
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