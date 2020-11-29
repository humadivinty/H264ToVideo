#ifndef LIBVIDEO_SAVER_FF_H
#define LIBVIDEO_SAVER_FF_H

//#include "libvideo_saver_ff_global.h"

//class LIBVIDEO_SAVER_FFSHARED_EXPORT Libvideo_saver_ff
//{

//public:
//    Libvideo_saver_ff();
//};

#ifdef WIN32

#define DELSPEC /*__stdcall*/
#ifdef LIBVIDEO_SAVER_FFSHARED_EXPORT
#define LIBVIDEO_SAVER_API __declspec(dllexport)
#else
#define LIBVIDEO_SAVER_API __declspec(dllimport)
#endif

#else

#define DELSPEC
#define LIBVIDEO_SAVER_API

#endif

#ifdef __cplusplus
extern "C"
{
#endif

LIBVIDEO_SAVER_API void* DELSPEC Video_CreateProcessHandle();
LIBVIDEO_SAVER_API int DELSPEC Video_CreateVideoFile(void* pHandle, const char* chFileName, int iFrameRate);
LIBVIDEO_SAVER_API int DELSPEC Video_WriteH264Frame(void* pHandle, int iFrameType, unsigned char* pbFrameData, int iFrameSize);
LIBVIDEO_SAVER_API int DELSPEC Video_CloseVideoFile(void* pHandle);
LIBVIDEO_SAVER_API int DELSPEC Video_CloseProcessHandle(void* pHandle);

#ifdef __cplusplus
}
#endif

#endif // LIBVIDEO_SAVER_FF_H
