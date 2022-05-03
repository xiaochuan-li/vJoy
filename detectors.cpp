#include "detectors.h"
#include <iostream>
using namespace std;

void assign(const char * &dest, const string &str)
{

    char * myroot = (char*) malloc(sizeof(char)*1024);
    strncpy_s(myroot, 1024, str.c_str(), str.size());
    dest = myroot;
}


std::vector<DetectorConfig> getConfigs(){

    string root = QCoreApplication::applicationDirPath().toStdString()+"/mediapipe/";
    DetectorConfig faceConfig;
    assign(faceConfig.root, root);
    assign(faceConfig.name, "Face Detector");
    assign(faceConfig.dllPath,  (root + "face_mesh_cpu_extern.dll"));
    assign(faceConfig.pbText, (root + "face_desktop_live.pbtxt"));
    assign(faceConfig.outputStream, "multi_face_landmarks");
    assign(faceConfig.modulePath, root + "modules");

    DetectorConfig handConfig;
    assign(handConfig.root, root);
    assign(handConfig.name, "Hand Detector");
    assign(handConfig.dllPath,  (root + "face_mesh_cpu_extern.dll"));
    assign(handConfig.pbText, (root + "hand_desktop_live.pbtxt"));
    assign(handConfig.outputStream, "landmarks");
    assign(handConfig.modulePath, root + "modules");

    return std::vector<DetectorConfig> {faceConfig, handConfig};
}
