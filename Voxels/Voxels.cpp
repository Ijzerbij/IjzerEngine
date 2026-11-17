#include "Voxels.hpp"

#include <chrono>

int main()
{
	// start with clock
	auto GameStartTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point lastFrameTime;

	// now start up the engine
	Eng::Engine myEngine;

	// now lets make the game ready

	// now lets run the game loop
	while (true)
	{
		// frame time
		auto now = std::chrono::steady_clock::now();
		auto elapsed = now - lastFrameTime;
		lastFrameTime = now;
		Eng::deltaTime dt = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

		// game update


		// engine update
		myEngine.Update(dt);
	}
	return 0;
}