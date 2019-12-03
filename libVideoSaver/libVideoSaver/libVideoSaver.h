// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBVIDEOSAVER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBVIDEOSAVER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
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