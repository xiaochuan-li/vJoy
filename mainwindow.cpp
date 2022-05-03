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
    configs = getConfigs();

    hotkey = new QHotkey (QKeySequence("Ctrl+Q"), true, this);
    hotkeySwitch = new QHotkey (QKeySequence("Ctrl+S"), true, this);
    QObject::connect(hotkey, &QHotkey::activated, this, &MainWindow::closeWindow);
    QObject::connect(hotkeySwitch, &QHotkey::activated, ctrl, &Controller::changeState);

    tp = new QSystemTrayIcon(this);
    tp->setIcon(QIcon(":/statics/statics/game.png"));
    menu = new QMenu();

    action = new QAction("&退出(Exit)");
    connect(action, &QAction::triggered, this, &MainWindow::closeWindow);

    AG=new QActionGroup(this);
    for(int i=0;i<configs.size();i++){
        auto action = new QAction(configs[i].name);
        AG->addAction(action);
        action->setCheckable(true);
        actionlist.push_back(action);
        menu->addAction(action);
    }
    connect(AG,&QActionGroup::triggered,this,
            [=]()mutable
    {
        for(int i=0; i< actionlist.size(); i++){
            if (actionlist[i]->isChecked()){
                qDebug() << "check" << configs[i].isValid();
                if(configs[i].isValid()){
                    ctrl->setMediapipe(configs[i]);
                }else{
                    char info[10240];
                    configs[i].print(info);
                    qDebug() << "CONFIG NOT VALID: "<< info;
                }
                break;
            }
        }
    }
    );

    menu->addAction(action);
    tp->setContextMenu(menu);
    tp->show();

}
void MainWindow::closeWindow(){
    tp->setVisible(false);
    close();
    emit pageClose();
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
    for(int i=0;i<actionlist.size();i++){
        delete actionlist[i];
    }
    delete AG;
}

