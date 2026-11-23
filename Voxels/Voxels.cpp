#include "Voxels.hpp"

#include <chrono>
#include <iostream>

int main()
{
	// start with clock
	auto GameStartTime = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point lastFrameTime;

	// now start up the engine
	Eng::Engine myEngine;

	// lets get a main window
	int mainScreenId = 1;
	myEngine.InitScreen(mainScreenId);
	myEngine.m_WindowMap.at(mainScreenId).Init(std::string("Voxels"), 1280, 720, true);
	
	// lets make a refrence to the window i know this isnt the best way, but its easy to work with and as windows are part of the engine I let engine do the clean up
	Eng::Window& mainWindow = myEngine.m_WindowMap.at(mainScreenId);
	mainWindow.maximize();
	// now lets make the game ready


	// now lets run the game loop
	bool shouldStop = false;
	while (!shouldStop)
	{
		// frame time
		auto now = std::chrono::steady_clock::now();
		auto elapsed = now - lastFrameTime;
		lastFrameTime = now;
		Eng::deltaTime dt = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

		// window updates
		mainWindow.pollEvents();


		// game update


		// engine update

		myEngine.Update(dt);


		shouldStop |= mainWindow.shouldClose();
	}

	return 0;
}