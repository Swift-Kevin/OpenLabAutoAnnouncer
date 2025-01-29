#include <iostream>
#include <string>

#include "App.h"

// make sure main has variadic args
int main()
{
	Configs config;
	std::string winTitle = config.at("Project").at("title").as<std::string>();
	int winWidth = config.at("Project").at("winWidth").as<int>();
	int winHeight = config.at("Project").at("winHeight").as<int>();


	return 0;
}
