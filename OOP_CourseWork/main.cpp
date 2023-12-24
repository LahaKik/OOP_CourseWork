#include <qcoreapplication.h>
#include <time.h>
#include "App.h"
#include "RasterWindow.h"
#include "Rack.h"
#include "GraphicWidget.h"

int main(int argc, char *argv[])
{
    srand(time(0));

    App app(argc, argv);
    



    return app.exec();
}
