#include <QDebug>
#include <QApplication>
#include "CombatModuleWidget.h"
#include "Compass.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    CombatModuleWidget w("CombatModuleWidget");
    w.setEditControl(false);
    w.show();
    Compass c("CompassWidget");
    c.setEditControl(false);
    c.show();


    return a.exec();
}
