#include "Core/Engine.hpp"
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
	void Engine::Update(deltaTime dt)
	{
		std::cout << dt << std::endl;
	}
}

