#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

App::App() {

}

App::~App() {
	
}

bool App::OnInit() {
	MainWindow* main = new MainWindow;
	main->Show();
	return true;
}