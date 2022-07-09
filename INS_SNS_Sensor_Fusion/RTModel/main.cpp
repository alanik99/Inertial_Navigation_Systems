// main.cpp:
#include "core.h"

#include <NavLib/Settings>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Settings settings;
    settings.parse("../settings.ini");

    Core core(&settings);
    core.start();

    return app.exec();
}
