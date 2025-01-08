#pragma once

#include "inicpp.h"
#include "Utilities.h"

class Configs : public ini::IniFile
{
public:
	Configs();
	void Shutdown();
};

