#include "src/Screens/MainScreen/mainscreen.h"
#include "src/Screens/Loadings/loadingscreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainScreen w;
    w.Start();

    return a.exec();
}
