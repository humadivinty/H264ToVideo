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
    printf("%s::  VideoType = %d", __FUNCTION__, VideoType);
    if (videoType_avi != VideoType
        && videoType_mp4 != VideoType)
    {
        printf("%s:: input type is invalid, must be 0%d or %d.\n", __FUNCTION__, videoType_avi, videoType_mp4);
        return 0;
    }
    CVideoSaver* pVideoSaver = new CVideoSaver(VideoType);
    return pVideoSaver;
}

LIBVIDEOSAVER_API int DELSPEC Video_CreateVideoFile(void *pHandle, const char *chFileName, int iVideoWidth, int iVideoHeight, int iFrameRate)
{
    printf("%s::  pHandle = %p, chFileName = %p, iVideoWidth = %d, iVideoHeight = %d, iFrameRate = %d",
        __FUNCTION__,
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
        printf("%s::parameter is invalid.\n", __FUNCTION__);
        return -1;
    }

    std::string strFile = Tool_ReplaceStringInStd(chFileName, "\\\\", "\\");
    strFile = Tool_ReplaceStringInStd(strFile.c_str(), "//", "/");
    printf("%s:: final file name = %s\n", __FUNCTION__, strFile.c_str());

    CVideoSaver* pVideoSaver = (CVideoSaver*)pHandle;
    int iRet = pVideoSaver->CreateVideoFile(strFile.c_str(),
        iVideoWidth,
        iVideoHeight,
        iFrameRate);

    printf("%s::return %d.\n", __FUNCTION__, iRet);
    return iRet;
}

LIBVIDEOSAVER_API int DELSPEC Video_WriteH264Frame(void *pHandle, int iFrameType, unsigned char *pbFrameData, int iFrameSize)
{
    printf("%s::  pHandle = %p, iFrameType = %d, pbFrameData = %p, iFrameSize = %d",
        __FUNCTION__,
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
        printf("%s::parameter is invalid.\n", __FUNCTION__);
        return -1;
    }

    CVideoSaver* pVideoSaver = (CVideoSaver*)pHandle;
    int iRet = pVideoSaver->WriteH264Frame(iFrameType, pbFrameData, iFrameSize);

    printf("%s::return %d.\n", __FUNCTION__, iRet);
    return iRet;
}

LIBVIDEOSAVER_API int DELSPEC Video_CloseVideoFile(void *pHandle)
{
    printf("%s::  pHandle = %p", __FUNCTION__, pHandle);
    if (NULL == pHandle)
    {
        printf("%s::parameter is invalid.\n", __FUNCTION__);
        return -1;
    }

    CVideoSaver* pVideoSaver = (CVideoSaver*)pHandle;
    int iRet = pVideoSaver->CloseVideoFile();

    printf("%s::return %d.\n", __FUNCTION__, iRet);
    return iRet;
}

LIBVIDEOSAVER_API int DELSPEC Video_CloseProcessHandle(void *pHandle)
{
    printf("%s::  pHandle = %p", __FUNCTION__, pHandle);
    if (NULL == pHandle)
    {
        printf("%s::parameter is invalid.\n", __FUNCTION__);
        return -1;
    }
    CVideoSaver* pVideoSaver = (CVideoSaver*)pHandle;
    SAFE_DELETE_OBJ(pVideoSaver);
    int iRet = 0;
    printf("%s::return %d.\n", __FUNCTION__, iRet);
    return iRet;
}