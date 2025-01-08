#include "App.h"

App::App()
{
	winTitle = config.at("Project").at("title").as<std::string>();
	winWidth = config.at("Project").at("winWidth").as<int>();
	winHeight = config.at("Project").at("winHeight").as<int>();
	
	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	scrWidth = displayMode.w;
	scrHeight = displayMode.h;
}

bool App::Init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER);
	window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_BORDERLESS);

	window = SDL_CreateWindow(winTitle.c_str(), 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, scrWidth, scrHeight, 
		window_flags);

	//variable that stores window manager information
	SDL_SysWMinfo wmInfo;
	//initializes current version of info so we can pass it to getwindowinfo
	SDL_VERSION(&wmInfo.version);
	//getter for window info and stores it inside wmInfo
	SDL_GetWindowWMInfo(window, &wmInfo);
	// extracts info from wmInfo and stores it inside HWND
	HWND hwnd = wmInfo.info.win.window;
	//Sets window style, allowing it to be transparent
	SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	// sets the window info of hwnd, LWA_COLORKEY sets it to transparent 0, 0, 0 color key is black, so any pixels matching will be transparent
	SetLayeredWindowAttributes(hwnd, 0, 1, LWA_COLORKEY);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = &ImGui::GetIO(); 
	(void)io;
	io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer2_Init(renderer); 
	
	return false;
}

bool App::Run()
{
	while (!done)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			ImGui_ImplSDL2_ProcessEvent(&event);
			if (event.type == SDL_QUIT)
				done = true;
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				done = true;

		}
		if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
		{
			SDL_Delay(10);
			continue;
		}

		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		
		// EXECUTING CODE HERE
		{
			ExecuteCode();
		}

		ImGui::Render();
		SDL_RenderSetScale(renderer, io->DisplayFramebufferScale.x, io->DisplayFramebufferScale.y);
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
		SDL_RenderPresent(renderer);
	}

	return true;
}

bool App::Shutdown()
{
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	config.Shutdown();

	return false;
}

void App::ExecuteCode()
{
	//WINDOWS AND BUTTONS GO HERE
	ImGui::Begin(winTitle.c_str());
	ImGui::End();
}
