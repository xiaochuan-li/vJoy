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
#include "externDetector.h"
#include "detectors.h"
#include <QActionGroup>
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
    QActionGroup *AG;
    std::vector<QAction *> actionlist;
    std::vector<DetectorConfig> configs;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void pageClose(void);
public slots:
    void closeWindow(void);

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
