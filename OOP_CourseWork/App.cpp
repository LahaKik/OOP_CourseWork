#include "App.h"


App::App(int argc, char** argv) : QApplication(argc, argv)
{
	GW = new GraphicWidget();
	
	GW->showFullScreen();
}