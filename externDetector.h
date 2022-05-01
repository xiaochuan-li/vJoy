
#ifndef __EXTERNDETECTOR_H__    //意思是  "if not define __XXX_H__" 也就是没包含XXX.h

#define __EXTERNDETECTOR_H__   //就定义__XXX_H__

#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#ifdef _DLL_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif
class ExternDetector{
    public:
    virtual void _init(const char* buf, const uint64_t buf_size)=0;
    virtual void update(cv::Mat&, float*, bool&)=0;
    virtual void destroy(void)=0;
};

extern "C" DLL_API ExternDetector *getDetector();

#endif
