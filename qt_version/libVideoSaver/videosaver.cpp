#include "videosaver.h"
#include"libvideo_typedef.h"
#include<stdio.h>
#include<string.h>
#include"utilityTool/ToolFunction.h"t"

CVideoSaver::CVideoSaver(int iVideoType):
    m_iVideoType(iVideoType)
{
    OUT_LOG(" iVideoType = %d  " , iVideoType);
}

CVideoSaver::~CVideoSaver()
{
    OUT_LOG(" begin  " );
    CloseVideoFile();
    OUT_LOG(" finish  " );
}

int CVideoSaver::CreateVideoFile(const char *chFileName, int iVideoWidth, int iVideoHeight, int iFrameRate)
{
    int iRet = -1;
    if(NULL == chFileName
            || strlen(chFileName) <=0
            || (NULL == strstr(chFileName, ".avi") && NULL == strstr(chFileName, ".mp4") )
            || iVideoWidth <= 0
            || iVideoHeight<= 0
            || iFrameRate<=0 )
    {
        OUT_LOG(" parameter is invalid.  chFileName = %p,  iVideoWidth = %d,  iVideoHeight = %d,  iFrameRate = %d  ",
                chFileName,
                iVideoWidth,
                iVideoHeight,
                iFrameRate );
        return -2;
    }
    OUT_LOG("  chFileName = %s,  iVideoWidth = %d,  iVideoHeight = %d,  iFrameRate = %d  ",
            chFileName,
            iVideoWidth,
            iVideoHeight,
            iFrameRate );

    if(videoType_avi == m_iVideoType )
    {
        if(!m_264AviLib.IsNULL())
        {
            m_264AviLib.close();
        }
        m_264AviLib.setAviInfo((char*)chFileName, iVideoWidth, iVideoHeight, iFrameRate, "H264");

        iRet = 0;
    }
    else if(videoType_mp4 == m_iVideoType )
    {
        m_264Mp4Lib.FileClose();
        iRet = m_264Mp4Lib.FileCreate(chFileName, iVideoWidth, iVideoHeight, iFrameRate);
    }
    OUT_LOG(" return = %d  " ,iRet);
    return iRet;
}

int CVideoSaver::WriteH264Frame( int iFrameType, unsigned char *pbFrameData, int iFrameSize)
{
    if((videoType_avi == m_iVideoType) && (frameType_avi_I_frame != iFrameType  && frameType_avi_P_frame != iFrameType )
            || (videoType_mp4 == m_iVideoType) && ( iFrameType < frameType_mp4_video  ||  iFrameType > frameType_avi_P_frame  )
            || (videoType_avi != m_iVideoType && videoType_mp4 != m_iVideoType )
            || NULL == pbFrameData
            || iFrameSize <= 0
            )
    {
        OUT_LOG(" parameter is invalid, iFrameType = %d,  pbFrameData = %p,  iFrameSize = %d  ",
                iFrameType,
                pbFrameData,
                iFrameSize );
        return -2;
    }
    int iRet = -1;
    OUT_LOG("  iFrameType = %d,  pbFrameData = %p,  iFrameSize = %d  ",
            iFrameType,
            pbFrameData,
            iFrameSize );

    if(videoType_avi == m_iVideoType )
    {
        if (!m_264AviLib.IsNULL() )
        {
            int iIsIframe = (iFrameType == frameType_avi_I_frame) ? 1: 0;
            iRet = m_264AviLib.writeFrame((char*)pbFrameData, iFrameSize, iIsIframe);
        }
        else
        {
            iRet = -3;
            OUT_LOG(" m_264AviLib.IsNULL() iRet = %d   " , iRet);
        }
    }
    else if(videoType_mp4 == m_iVideoType )
    {
        int iType = 0;
        switch (iFrameType)
        {
        case frameType_avi_I_frame:
        case frameType_avi_P_frame:
        case frameType_mp4_video:
            iType = MEDIA_FRAME_VIDEO;
            break;
        case frameType_mp4_audio:
            iType = MEDIA_FRAME_AUDIO;
            break;

        default:
            iType = MEDIA_FRAME_UNVALID;
            break;
        }
        iRet = m_264Mp4Lib.FileWrite(iType, pbFrameData, iFrameSize);
    }
    OUT_LOG(" return = %d  " , iRet);
    return iRet;
}

int CVideoSaver::CloseVideoFile()
{
    OUT_LOG("begin,  type = %d  " , m_iVideoType);
    int iRet = -1;
    if(videoType_avi == m_iVideoType )
    {
        if(!m_264AviLib.IsNULL())
        {
            m_264AviLib.close();
        }
        iRet = 0;
    }
    else if(videoType_mp4 == m_iVideoType )
    {
        iRet =  m_264Mp4Lib.FileClose();
    }
    OUT_LOG("finish " );
    return iRet;
}
