#include "mainwindow.h"


#include <QApplication>
#include "ui.h"
UI *ui;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ui = new UI;
    ui->displaymenu();
    ui->show();
    return a.exec();
}
