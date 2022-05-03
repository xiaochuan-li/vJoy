
#ifndef __EXTERNDETECTOR_H__ //意思是  "if not define __XXX_H__" 也就是没包含XXX.h

#define __EXTERNDETECTOR_H__ //就定义__XXX_H__

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/stat.h>
#define S_ISREG(m)      (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)      (((m) & S_IFMT) == S_IFDIR)
#ifdef _DLL_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif
template <typename T> const std::string pathJoin(T a, T b){
    return  (std::string(a) + "/" + std::string(b));
}

class DetectorConfig
{
public:
    const char *name=nullptr;
    const char *root=nullptr;
    const char *dllPath=nullptr;
    const char *pbText=nullptr;
    const char *outputStream=nullptr;
    const char *modulePath=nullptr;
    bool isValid(const char * path)
    {
        struct _stat fileStat;
        return ((_stat(path, &fileStat) == 0) && ((S_ISDIR(fileStat.st_mode)) || S_ISREG(fileStat.st_mode)));
    };
    bool isValid(const std::string path)
    {
        struct _stat fileStat;
        return ((_stat(path.c_str(), &fileStat) == 0) && ((S_ISDIR(fileStat.st_mode)) || S_ISREG(fileStat.st_mode)));
    };
    bool isValid(void){
        return (name!=nullptr) && (root!=nullptr) && (dllPath!=nullptr) && (pbText!=nullptr) && (outputStream!=nullptr) && (modulePath!=nullptr) && isValid(root) && isValid(dllPath) && isValid(pbText) && isValid( modulePath);
    }
    void print(char * targetString){
        std::string fmt("Name: %s\nRoot: %s\nDLLPath: %s\nPBTxt: %s\nStream: %s\nModule: %s\n");
        //char targetString[1024*10];
        snprintf(targetString,
                 1024*10,
                 fmt.c_str(),
                 name,
                 root,
                 dllPath,
                 pbText,
                 outputStream,
                 modulePath);
    }
};

class ExternDetector
{
public:
    virtual void _init(const char *, const char *) = 0;
    virtual void _init(DetectorConfig)=0;
    virtual void update(cv::Mat &, float *res, bool &) = 0;
    virtual void destroy(void) = 0;
};

extern "C" DLL_API ExternDetector *getDetector();

#endif
