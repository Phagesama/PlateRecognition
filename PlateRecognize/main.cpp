#include "platerecognize.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PlateRecognize w;
    w.show();

    return a.exec();
}
