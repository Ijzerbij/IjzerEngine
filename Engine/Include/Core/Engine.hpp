#pragma once

#include "Core/Common.hpp"
#include "Window/Window.hpp"

#include<unordered_map>

namespace Eng 
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		void Update(deltaTime dt);

		void InitScreen(int screenId);
		std::unordered_map<int, Window> m_WindowMap;
	private:
	};
}