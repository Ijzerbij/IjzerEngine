#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace Eng
{
	namespace GLFW // GLFW global window functions and data
	{
		static int g_glfwRefCount = 0;

		std::string glfwErrorString();
	}

	class Window
	{
	public:
		Window();
		~Window();

		// preventing the window from being coppied so no one can accidentally own a coppy of a window and delete the actaul data
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;



	private:
		GLFWwindow*  m_window;
		VkInstance   m_instance;
		VkSurfaceKHR m_surface;
		bool         m_resized;
		bool         m_ownsGlfwRef;
	};
}