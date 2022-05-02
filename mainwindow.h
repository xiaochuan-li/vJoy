#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QString>
#include <QIcon>
#include <QFileDialog>
#include <QHotkey>
#include <QKeyEvent>
#include <QDialog>
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QHotkey *hotkey, *hotkeySwitch;
    QSystemTrayIcon *tp;
    QAction* action;
    QMenu *menu;
    Controller * ctrl;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void pageClose(void);
public slots:
    void closeWindow(void);
    void browse(){
        QString file_name = QFileDialog::getExistingDirectory(this,"Mediapipe Directory",".");
        if(file_name.compare("") != 0 ){
            ctrl->setMediapipe(file_name);
        }
    }

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
