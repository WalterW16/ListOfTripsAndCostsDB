#include "stdafx.h"
#include "ListOfTripsAndCosts.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListOfTripsAndCosts w;
    w.show();
    return a.exec();
}
