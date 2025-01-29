#include "App.h"

wxIMPLEMENT_APP(App);

App::App() {
}

App::~App() {
}

bool App::OnInit() {
	ENABLE_LEAK_DETECTION();

	MainWindow* mainWindow = new MainWindow();
	mainWindow->Show();
	return true;
}