#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QProcess>
#include <QTimer>
#include <QString>
#include <QApplication>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include "externDetector.h"
#include <QDir>
#include <QLibrary>

#include <windows.h>
#include "stick.h"
typedef ExternDetector* (*createDetector)();

class ExpSmoother{
public:
    float x=-1, y=-1;
    float alpha;
    ExpSmoother(float _alpha=0.5){
        alpha = _alpha;
    };
    void update(float& _x, float& _y){
        if(x==-1 && y==-1){
            return ;
        }else{
            x = alpha*x + (1-alpha)*_x;
            y = alpha*y + (1-alpha)*y;
            _x = x;
            _y = y;
        }
    }
    void reset(){
        x = -1;
        y = -1;
    }
};

class Controller : public QObject
{
    Q_OBJECT
public:
    QTimer *timer;
    //QProcess *process;
    Stick * stick;
    ExternDetector* det;
    ExpSmoother *smoother;

    cv::VideoCapture cap;
    float *res;
    cv::Mat frame;
    float base_x=-1, base_y=-1;
    QString mediapipePath;
    bool state=false;


    explicit Controller(QObject *parent = nullptr);

    bool isReady(){
        return !mediapipePath.compare("");
    }
    ~Controller();

signals:
    void updateStr(QString& str);
public slots:
    void sendSignal();
    void setMediapipe(QString path);
    void changeState();

};

#endif // CONTROLLER_H
