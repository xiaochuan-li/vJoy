#include "mainwindow.h"

#include <QSharedMemory>

#include <QMessageBox>
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QObject::connect(&w, SIGNAL(pageClose()),&a,SLOT(quit()));
    QSharedMemory shared("vJoy");
    if(shared.attach())
    {
        QMessageBox::information(NULL,QStringLiteral("Warning"),QStringLiteral("Application is alreadly running!"));
        return 0;
    }
    w.show();

    shared.create(1);
    return a.exec();
}
