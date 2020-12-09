#include "libvideo_saver_ff.h"
#include "H264ToMp4.h"
#include "Tool_function.h"

#ifdef __cplusplus
extern "C"
{
#endif

LIBVIDEO_SAVER_API void * DELSPEC_VIDEO Video_CreateProcessHandle()
{
    H264ToMp4* pProcesser = new H264ToMp4();
    if(!pProcesser)
    {
        OUT_LOG("alloc video processor failed.");
        return NULL;
    }
    return pProcesser;
}

LIBVIDEO_SAVER_API int DELSPEC_VIDEO Video_CreateVideoFile(void *pHandle, const char *chFileName, int iFrameRate)
{
    OUT_LOG("pHandle = %p, chFileName = %s, iFrameRate = %d.", pHandle , chFileName, iFrameRate);
    H264ToMp4* pProcesser = static_cast<H264ToMp4*>(pHandle);
    if(!pProcesser)
    {
        OUT_LOG("alloc video processor failed.");
        return -1;
    }
    int iRet = pProcesser->create_videoFile(chFileName);
    OUT_LOG("finish, return %d", iRet);
    return iRet;
}

LIBVIDEO_SAVER_API int DELSPEC_VIDEO Video_WriteH264Frame(void *pHandle, int iFrameType, unsigned char *pbFrameData, int iFrameSize)
{
    OUT_LOG("pHandle = %p, iFrameType = %d, pbFrameData = %p, iFrameSize = %d.", pHandle , iFrameType, pbFrameData, iFrameSize);
    H264ToMp4* pProcesser = static_cast<H264ToMp4*>(pHandle);
    if(!pProcesser)
    {
        OUT_LOG("alloc video processor failed.");
        return -1;
    }
    pProcesser->add_frame(pbFrameData, iFrameSize);
    int iRet = 0;
    OUT_LOG("finish, return %d", iRet);
    return iRet;
}

LIBVIDEO_SAVER_API int DELSPEC_VIDEO Video_CloseVideoFile(void *pHandle)
{
    OUT_LOG("pHandle = %p");
    H264ToMp4* pProcesser = static_cast<H264ToMp4*>(pHandle);
    if(!pProcesser)
    {
        OUT_LOG("alloc video processor failed.");
        return -1;
    }
    int iRet = pProcesser->finish_save_video();
    OUT_LOG("finish, return %d", iRet);
    return iRet;
}

LIBVIDEO_SAVER_API int DELSPEC_VIDEO Video_CloseProcessHandle(void *pHandle)
{
    OUT_LOG("pHandle = %p");
    H264ToMp4* pProcesser = static_cast<H264ToMp4*>(pHandle);
    if(!pProcesser)
    {
        OUT_LOG("alloc video processor failed.");
        return -1;
    }

    delete pProcesser;
    pProcesser = NULL;

    int iRet = 0;
    OUT_LOG("finish, return %d", iRet);
    return iRet;
}


#ifdef __cplusplus
}
#endif
