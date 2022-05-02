#include "controller.h"



Controller::Controller(QObject *parent)
    : QObject{parent}
{
    res = new float[512*4];
    timer = new QTimer(this);
    stick = new Stick();
    //process = new QProcess(this);
    smoother = new ExpSmoother(0.5);
    det = nullptr;
}

void Controller::sendSignal(){
    cap >> frame;
    if(frame.empty()) return;
    bool updated=false;
    det->update(frame, res, updated);
    if(updated){
        float x = res[0];
        float y = 1 - res[1];
        smoother->update(x, y);
        if (base_x==-1 && base_y==-1){
            base_x = x;
            base_y = y;
        }else{
            x = x - base_x;
            y = y - base_y;
            stick->update(x*2, y*2);
        }
    }
}

void Controller::setMediapipe(QString path){
    mediapipePath = path;
    QString DllPath = mediapipePath + QString("/face_mesh_cpu_extern.dll");
    QLibrary mylib(DllPath);
    if (mylib.load())
    {
        createDetector getDetector=(createDetector)mylib.resolve("getDetector");    //援引 add() 函数
        if (getDetector)
        {
            QString pbPath = mediapipePath + QString("/face_mesh_desktop_live.pbtxt");
            det = getDetector();
            det->_init(pbPath.toStdString().c_str(), pbPath.size());
        }
    }
    connect(timer, &QTimer::timeout, this, &Controller::sendSignal);
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
        if (mediapipePath.compare("")!= 0)
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
    //process->kill();
    cap.release();
    delete timer;
    //delete process;
    delete res;
    delete stick;
    delete smoother;
}
