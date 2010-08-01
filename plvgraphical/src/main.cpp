#include <QApplication>
#include <iostream>
#include <QDebug>

#include <Application.h>

#include "MainWindow.h"
#include "ElementConfigFormBuilder.h"
#include "CameraConfigFormBuilder.h"

using namespace plv;
using namespace plvgui;

int main(int argc, char **argv)
{
    Q_INIT_RESOURCE(icons);
    QApplication app(argc, argv);

    plvRegisterConfigFormBuilder<plvgui::CameraConfigFormBuilder>
                    ("plv::CameraProducer", "plvgui::CameraConfigFormBuilder");

    Application parlevision(&app);
    parlevision.init();

    MainWindow* mainWin = new MainWindow();

    mainWin->show();

    int retval = app.exec();

    return retval;
}