#pragma once
#include <qobject.h>
#include <qapplication.h>
#include "GraphicWidget.h"
#include "Rack.h"

class App : public QApplication
{
private:
	Q_OBJECT
	GraphicWidget* GW;

public:
	App(int, char**);
};

