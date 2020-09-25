#include "stdafx.h"
#include "videosaver.h"
#include"libvideo_typedef.h"
#include "utilityTool/ToolFunction.h"
#include<stdio.h>
#include<string.h>

CVideoSaver::CVideoSaver(int iVideoType):
   m_iVideoType(iVideoType)
{
    PRINT_INFO(" iVideoType = %d\n",   iVideoType);
}

CVideoSaver::~CVideoSaver()
{
    PRINT_INFO(" begin\n");
    CloseVideoFile();
    PRINT_INFO(" finish\n");
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
        PRINT_INFO(" parameter is invalid.  chFileName = %p,  iVideoWidth = %d,  iVideoHeight = %d,  iFrameRate = %d\n",               
               chFileName,
               iVideoWidth,
               iVideoHeight,
               iFrameRate );
        return -2;
    }
    PRINT_INFO("  chFileName = %p,  iVideoWidth = %d,  iVideoHeight = %d,  iFrameRate = %d\n",           
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
    PRINT_INFO(" return = %d\n",  iRet);
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
        PRINT_INFO(" parameter is invalid, iFrameType = %d,  pbFrameData = %p,  iFrameSize = %d\n",               
               iFrameType,
               pbFrameData,
               iFrameSize );
        return -2;
    }
    int iRet = -1;
    PRINT_INFO("  iFrameType = %d,  pbFrameData = %p,  iFrameSize = %d\n",           
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
            PRINT_INFO(" m_264AviLib.IsNULL() iRet = %d \n",   iRet);
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
    PRINT_INFO(" return = %d\n",   iRet);
    return iRet;
}

int CVideoSaver::CloseVideoFile()
{
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
    return iRet;
}
