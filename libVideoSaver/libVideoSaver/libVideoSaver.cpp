// libVideoSaver.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "libVideoSaver.h"
#include "videosaver.h"
#include "stdio.h"
#include "libvideo_typedef.h"
#include "utilityTool/ToolFunction.h"


#define SAFE_DELETE_OBJ(obj) \
if (NULL != obj)                                  \
{                                           \
    delete obj;                        \
    obj = NULL;                      \
}

LIBVIDEOSAVER_API void* DELSPEC Video_CreateProcessHandle(int VideoType)
{
    PRINT_INFO(" VideoType = %d", VideoType);
    if (videoType_avi != VideoType
        && videoType_mp4 != VideoType)
    {
        PRINT_INFO("input type is invalid, must be 0%d or %d.\n", videoType_avi, videoType_mp4);
        return 0;
    }
    CVideoSaver* pVideoSaver = new CVideoSaver(VideoType);
    return pVideoSaver;
}

LIBVIDEOSAVER_API int DELSPEC Video_CreateVideoFile(void *pHandle, const char *chFileName, int iVideoWidth, int iVideoHeight, int iFrameRate)
{
    PRINT_INFO(" pHandle = %p, chFileName = %p, iVideoWidth = %d, iVideoHeight = %d, iFrameRate = %d",        
        pHandle,
        chFileName,
        iVideoWidth,
        iVideoHeight,
        iFrameRate);

    if (NULL == pHandle
        || NULL == chFileName
        || iVideoWidth <= 0
        || iVideoHeight <= 0
        || iFrameRate <= 0)
    {
        PRINT_INFO("parameter is invalid.\n");
        return -1;
    }

    std::string strFile = Tool_ReplaceStringInStd(chFileName, "\\\\", "\\");
    strFile = Tool_ReplaceStringInStd(strFile.c_str(), "//", "/");
    PRINT_INFO("final file name = %s\n", strFile.c_str());

    CVideoSaver* pVideoSaver = (CVideoSaver*)pHandle;
    int iRet = pVideoSaver->CreateVideoFile(strFile.c_str(),
        iVideoWidth,
        iVideoHeight,
        iFrameRate);

    PRINT_INFO("return %d.\n", iRet);
    return iRet;
}

LIBVIDEOSAVER_API int DELSPEC Video_WriteH264Frame(void *pHandle, int iFrameType, unsigned char *pbFrameData, int iFrameSize)
{
    PRINT_INFO(" pHandle = %p, iFrameType = %d, pbFrameData = %p, iFrameSize = %d",        
        pHandle,
        iFrameType,
        pbFrameData,
        iFrameSize);

    if (NULL == pHandle
        || (frameType_avi_I_frame != iFrameType  && frameType_avi_P_frame != iFrameType && videoType_avi != iFrameType && videoType_mp4 != iFrameType)
        || NULL == pbFrameData
        || iFrameSize <= 0
        )
    {
        PRINT_INFO("parameter is invalid.\n");
        return -1;
    }

    CVideoSaver* pVideoSaver = (CVideoSaver*)pHandle;
    int iRet = pVideoSaver->WriteH264Frame(iFrameType, pbFrameData, iFrameSize);

    PRINT_INFO("return %d.\n", iRet);
    return iRet;
}

LIBVIDEOSAVER_API int DELSPEC Video_CloseVideoFile(void *pHandle)
{
    PRINT_INFO(" pHandle = %p", pHandle);
    if (NULL == pHandle)
    {
        PRINT_INFO("parameter is invalid.\n");
        return -1;
    }

    CVideoSaver* pVideoSaver = (CVideoSaver*)pHandle;
    int iRet = pVideoSaver->CloseVideoFile();

    PRINT_INFO("return %d.\n", iRet);
    return iRet;
}

LIBVIDEOSAVER_API int DELSPEC Video_CloseProcessHandle(void *pHandle)
{
    PRINT_INFO(" pHandle = %p", pHandle);
    if (NULL == pHandle)
    {
        PRINT_INFO("parameter is invalid.\n");
        return -1;
    }
    CVideoSaver* pVideoSaver = (CVideoSaver*)pHandle;
    SAFE_DELETE_OBJ(pVideoSaver);
    int iRet = 0;
    PRINT_INFO("return %d.\n", iRet);
    return iRet;
}