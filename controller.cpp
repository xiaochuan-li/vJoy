#include "controller.h"

float bound(float a, float l, float h){
    return (a<l?a:(a>h?h:a));
}

Controller::Controller(QObject *parent)
    : QObject{parent}
{
    res = new float[512*4];
    timer = new QTimer(this);
    stick = new Stick();
    //process = new QProcess(this);
    smoother = new ExpSmoother(0.5);
    connect(timer, &QTimer::timeout, this, &Controller::sendSignal);

    det = nullptr;
}

void Controller::sendSignal(){
    cap >> frame;
    if(frame.empty()) return;
    bool updated=false;
    det->update(frame, res, updated);
    if(updated){
        float x = (res[5*3] + res[9*3] +res[13*3])/3;
        float y = 1 - (res[5*3+1] + res[9*3+1] +res[13*3+1])/3;
        smoother->update(x, y);
        if (base_x==-1 && base_y==-1){
            base_x = x;
            base_y = y;
        }else{
            x = x - base_x;
            y = y - base_y;
            x = x*2;
            y = y*2;
            stick->update(bound(x, -1, 1), bound(y, -1, 1));
        }
    }
}

void Controller::setMediapipe(DetectorConfig config){

    QLibrary mylib(config.dllPath);
    if (mylib.load())
    {
        createDetector getDetector=(createDetector)mylib.resolve("getDetector");    //援引 add() 函数
        if (getDetector)
        {
            det = getDetector();
            det->_init(config);
        }
    }
    ready=true;
}
void Controller::changeState(){
    if(state){
        timer->stop();
        if (cap.isOpened()){
            cap.release();
        }
        base_x = -1;
        base_y = -1;
        smoother->reset();
        state = !state;

    }else{
        if (ready)
        {
            timer->start(20);
            if (!cap.isOpened()){
                cap.open(0);
            }
            state = !state;

        }
    }
}
Controller::~Controller(){
    timer->stop();
    cap.release();
    delete timer;
    delete res;
    delete stick;
    delete smoother;
}
