#pragma once
#include "Defines.h"
#include "Configs.h"

class App
{
private:
	std::string appTitle = "";
	Configs config;
	bool done = false;

	// SDL Items
	SDL_WindowFlags window_flags;
	SDL_DisplayMode displayMode;
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	ImGuiIO* io;

	// Screen and Window Items
	int winWidth = 0;
	int winHeight = 0;
	std::string winTitle = "";

public:
	App();

	bool Init();
	bool Run();
	bool Shutdown();

	virtual void ExecuteCode();
};

