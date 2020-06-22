#ifndef VIDEOSAVER_H
#define VIDEOSAVER_H
#include"libAVI/cAviLib.h"
#include"libMp4/cMp4Encode.h"

class CVideoSaver
{
public:
    CVideoSaver(int iVideoType);
    ~CVideoSaver();

    int CreateVideoFile(const char* chFileName, int iVideoWidth, int iVideoHeight, int iFrameRate);
    int WriteH264Frame(int iFrameType, unsigned char* pbFrameData, int iFrameSize);
    int CloseVideoFile();

private:
    int m_iVideoType;
    CAviLib m_264AviLib;
    CMp4Encode m_264Mp4Lib;
};

#endif // VIDEOSAVER_H
