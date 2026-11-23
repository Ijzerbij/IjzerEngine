#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>
#include <vector>

namespace Eng
{
	struct VulkanRenderTarget {
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		VkExtent2D   extent = { 0, 0 }; // framebuffer size in pixels
	};

	namespace GLFW // GLFW global window functions and data
	{
		static int g_glfwRefCount = 0;

		void glfwErrorString();
	}

	class Window
	{
	public:
		Window();
		~Window();

		// preventing the window from being coppied so no one can accidentally own a coppy of a window and delete the actaul data
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		void StartGLFW();
		void StopGLFW();

		void Init(const std::string& title, uint32_t width, uint32_t height, bool resizable);

		VulkanRenderTarget createRenderTarget(VkInstance instance);

		void shutdown(); // destroys surface + window; also called by the destructor

		// Extensions Vulkan needs to present to a GLFW window. Callable before init().
		std::vector<const char*> requiredInstanceExtensions();

		void       pollEvents();
		void       waitEvents();          
		bool       shouldClose() const;
		bool       isMinimized() const;
		bool       consumeResized();      
		VkExtent2D framebufferExtent() const;

		void maximize();
		void restore();          // back to the previous size
		void toggleMaximized();
		bool isMaximized() const;

		GLFWwindow* handle() const { return m_window; }

	private:
		GLFWwindow*  m_window;
		VkInstance   m_instance;
		VkSurfaceKHR m_surface;
		bool         m_resized;
		bool         m_ownsGlfwRef;

		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
	};
}