#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ctrl = new Controller(this);
    ui->statusbar->setVisible(false);
    setWindowOpacity(0.8);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);

    setFixedSize(this->width(),this->height());
    hotkey = new QHotkey (QKeySequence("Ctrl+S"), true, this);
    hotkeySwitch = new QHotkey (QKeySequence("Ctrl+Q"), true, this);
    QObject::connect(hotkey, &QHotkey::activated, this, &MainWindow::browse);
    QObject::connect(hotkeySwitch, &QHotkey::activated, ctrl, &Controller::changeState);

    tp = new QSystemTrayIcon(this);
    tp->setIcon(QIcon(":/statics/statics/game.png"));
    action = new QAction("&退出(Exit)");

    connect(action, &QAction::triggered, this, [&](){
        tp->setVisible(false);
        close();
        emit pageClose();
    });
    menu = new QMenu();
    menu->addAction(action);
    tp->setContextMenu(menu);
    tp->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete hotkey;
    delete hotkeySwitch;
    delete tp;
    delete action;
    delete menu;
    delete ctrl;
}

