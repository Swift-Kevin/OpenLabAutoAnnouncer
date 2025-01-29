#pragma once
#include "Configs.h"

#include "MainWindow.h"

class App : public wxApp
{
private:

public:
	App();
	~App();
	virtual bool OnInit();
};

