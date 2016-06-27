#include "EmprestimoControler.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EmprestimoControler controler;
    controler.holidays();

    return a.exec();
}
