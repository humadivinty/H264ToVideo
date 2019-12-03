// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 LIBVIDEOSAVER_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// LIBVIDEOSAVER_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef LIBVIDEOSAVER_EXPORTS
#define LIBVIDEOSAVER_API __declspec(dllexport)
#else
#define LIBVIDEOSAVER_API __declspec(dllimport)
#endif

#define DELSPEC 

#define FRAMETYPE_MP4_VIDEO 0
#define FRAMETYPE_MP4_AUDIO 1
#define FRAMETYPE_AVI_I_FRAME 2
#define FRAMETYPE_AVI_P_FRAME 3

#define  VIDEOTYPE_AVI 0
#define  VIDEOTYPE_MP4 1

#ifdef __cplusplus
extern "C"
{
#endif

    LIBVIDEOSAVER_API void* DELSPEC Video_CreateProcessHandle(int VideoType);
    LIBVIDEOSAVER_API int DELSPEC Video_CreateVideoFile(void* pHandle, const char* chFileName, int iVideoWidth, int iVideoHeight, int iFrameRate);
    LIBVIDEOSAVER_API int DELSPEC Video_WriteH264Frame(void* pHandle, int iFrameType, unsigned char* pbFrameData, int iFrameSize);
    LIBVIDEOSAVER_API int DELSPEC Video_CloseVideoFile(void* pHandle);
    LIBVIDEOSAVER_API int DELSPEC Video_CloseProcessHandle(void* pHandle);

#ifdef __cplusplus
}
#endif