#include "Core/Engine.hpp"

#include "Core/Logging.hpp"

#include <iostream>

namespace Eng 
{
	Engine::Engine()
	{
		std::cout << "Engine be runnin" << std::endl;
	}

	Engine::~Engine()
	{
		std::cout << "Engine be runnin no more" << std::endl;
	}
	
	void Engine::InitScreen(int screenId)
	{
		if (m_WindowMap.contains(screenId))
		{
			std::cout << "window with ID: " << screenId << " already exists" << std::endl;
			logger::LogCritticalError(logger::window, screenId);
			return;
		}
		m_WindowMap.try_emplace(screenId);

		return;
	}

	void Engine::Update(deltaTime dt)
	{
		//std::cout << dt << std::endl;
	}
}

