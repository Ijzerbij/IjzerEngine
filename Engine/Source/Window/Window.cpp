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
		GLFW::g_glfwRefCount --;
		StopGLFW();
	}

	void Window::StartGLFW()
	{
		if (GLFW::g_glfwRefCount == 0) {
			if (!glfwInit()) {
				GLFW::g_glfwRefCount = 0;
				GLFW::glfwErrorString();
			}
			if (!glfwVulkanSupported())
				throw std::runtime_error("GLFW: Vulkan loader / ICD not found");
		}
	}

	void Window::StopGLFW()
	{
		
		if (m_surface != VK_NULL_HANDLE) {
			vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
			m_surface = VK_NULL_HANDLE;
			m_instance = VK_NULL_HANDLE;
		}
		if (m_window) {
			glfwDestroyWindow(m_window);
			m_window = nullptr;
		}
		//if (m_ownsGlfwRef) {
		//	m_ownsGlfwRef = false;
		//	releaseGlfw();
		//}

		if (GLFW::g_glfwRefCount == 0)
			glfwTerminate();

		std::cout << "window cleaned up" << std::endl;
	}

	void Window::Init(const std::string& title, uint32_t width, uint32_t height, bool resizable)
	{
		if (m_window)
			throw std::logic_error("Window::init called twice");

		StartGLFW();

		GLFW::g_glfwRefCount++;

		m_ownsGlfwRef = true;

		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, resizable ? GLFW_TRUE : GLFW_FALSE);

		m_window = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height),
			title.c_str(), nullptr, nullptr);
		if (!m_window) {
			GLFW::glfwErrorString();
		}

		glfwSetWindowUserPointer(m_window, this);
		glfwSetFramebufferSizeCallback(m_window, &Window::framebufferResizeCallback);
	}

	VulkanRenderTarget Window::createRenderTarget(VkInstance instance)
	{
		if (!m_window)
			throw std::logic_error("Window::createRenderTarget called before init");
		if (m_surface != VK_NULL_HANDLE)
			throw std::logic_error("Window already has a render target");

		VkResult res = glfwCreateWindowSurface(instance, m_window, nullptr, &m_surface);
		if (res != VK_SUCCESS)
			throw std::runtime_error("glfwCreateWindowSurface failed (VkResult " +
				std::to_string(res) + ")");

		m_instance = instance;
		return { m_surface, framebufferExtent() };
	}

	std::vector<const char*> Window::requiredInstanceExtensions()
	{
		if (GLFW::g_glfwRefCount == 0)
		{
			StartGLFW();
		}

		uint32_t count = 0;
		const char** exts = glfwGetRequiredInstanceExtensions(&count);
		if (!exts)
		{
			GLFW::glfwErrorString();
		}

		return { exts, exts + count };
	}

	void Window::pollEvents()
	{
		glfwPollEvents();
	}

	void Window::waitEvents()
	{
		glfwWaitEvents();
	}

	bool Window::shouldClose() const
	{
		return m_window && glfwWindowShouldClose(m_window);
	}

	bool Window::isMinimized() const
	{
		VkExtent2D e = framebufferExtent();
		return e.width == 0 || e.height == 0;
	}

	bool Window::consumeResized()
	{
		bool r = m_resized;
		m_resized = false;
		return r;
	}

	VkExtent2D Window::framebufferExtent() const
	{
		int w = 0, h = 0;
		glfwGetFramebufferSize(m_window, &w, &h);
		return { static_cast<uint32_t>(w), static_cast<uint32_t>(h) };
	}

	void Window::maximize() 
	{
		glfwMaximizeWindow(m_window); 
	}

	void Window::restore() 
	{ 
		glfwRestoreWindow(m_window);
	}

	bool Window::isMaximized() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED) == GLFW_TRUE;
	}

	void Window::toggleMaximized() 
	{
		if (isMaximized()) restore();
		else               maximize();
	}

	void Window::framebufferResizeCallback(GLFWwindow* window, int width, int height)
	{
		if (auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window)))
			self->m_resized = true;
	}
}