#include "Configs.h"

// This code originates from the GFX courses and DEV 4/5 as of Jan. 1st, 2025

#include <filesystem>
using namespace std::chrono_literals;

Configs::Configs()
{
	// load ini file
	const char* defaults = "./defaults.ini";
	const char* saved = "./saved.ini";

	// if they both exist choose the newest one
	if (std::filesystem::exists(defaults) && std::filesystem::exists(saved)) 
	{
		// Load the newer file
		auto dtime = std::filesystem::last_write_time(defaults);
		auto stime = std::filesystem::last_write_time(saved);
		
		if (dtime > stime)
		{
			// defaults were tweaked
			(*this).load(defaults); 
		}
		else
		{
			// what happens most of the time
			(*this).load(saved); 
		}
	}
	// probably the first run after install
	else if (std::filesystem::exists(defaults)) 
	{ 
		(*this).load(defaults);
	}
	// the default file is missing or corrupted, this is bad
	else 
	{ 
		// a more graceful approach would be to overwrite defaults.ini
		std::abort(); 
	}
}

void Configs::Shutdown()
{
	// Save current state of .ini to disk
	// Could be used for persisting user prefrences, highscores, savegames etc...
	(*this).save("../saved.ini");
}
