#include "ermainwindow.hxx"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ERMainWindow w;
    w.show();
    return a.exec();
}
