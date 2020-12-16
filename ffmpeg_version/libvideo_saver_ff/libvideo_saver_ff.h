#ifndef LIBVIDEO_SAVER_FF_H
#define LIBVIDEO_SAVER_FF_H

//#include "libvideo_saver_ff_global.h"

//class LIBVIDEO_SAVER_FFSHARED_EXPORT Libvideo_saver_ff
//{

//public:
//    Libvideo_saver_ff();
//};

#ifdef WIN32

#define DELSPEC_VIDEO
#ifdef LIBVIDEO_SAVER_FFSHARED_EXPORT
#define LIBVIDEO_SAVER_API __declspec(dllexport)
#else
#define LIBVIDEO_SAVER_API __declspec(dllimport)
#endif

#else

#define DELSPEC_VIDEO
#define LIBVIDEO_SAVER_API

#endif

#ifdef __cplusplus
extern "C"
{
#endif

LIBVIDEO_SAVER_API void* DELSPEC_VIDEO Video_CreateProcessHandle();
LIBVIDEO_SAVER_API int DELSPEC_VIDEO Video_CreateVideoFile(void* pHandle, const char* chFileName, int iVideoWidth, int iVideoHeight, int iFrameRate);
LIBVIDEO_SAVER_API int DELSPEC_VIDEO Video_WriteH264Frame(void* pHandle, int iFrameType, unsigned char* pbFrameData, int iFrameSize);
LIBVIDEO_SAVER_API int DELSPEC_VIDEO Video_CloseVideoFile(void* pHandle);
LIBVIDEO_SAVER_API int DELSPEC_VIDEO Video_CloseProcessHandle(void* pHandle);

#ifdef __cplusplus
}
#endif

#endif // LIBVIDEO_SAVER_FF_H
