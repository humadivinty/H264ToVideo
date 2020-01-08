// testTool_videoSaver.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "libVideoSaver.h"
#include <stdio.h>
#include <memory.h>



int _tmain(int argc, _TCHAR* argv[])
{
    const char* pFileName = "test.h264";
    unsigned char* pData = NULL;

    FILE* pFile = fopen(pFileName, "rb");
    int size = 0;
    if (pFile)
    {
        fseek(pFile, 0L, SEEK_END);
        size = ftell(pFile);
        fseek(pFile, 0L, SEEK_SET);

        pData = new unsigned char[size];
        if (pData)
        {
            memset(pData, 0, size);
            fread(pData, 1, size, pFile);
        }

        fclose(pFile);
        pFile = NULL;
    }
    else
    {
        printf("open  %s failed. \n", pFileName);
        return 0;
    }

    void* h264Handle = Video_CreateProcessHandle(VIDEOTYPE_MP4);
    if (h264Handle)
    {
        printf("Video_CreateProcessHandle success. \n");

        int iRet = Video_CreateVideoFile(h264Handle, "test.mp4", 1920, 1080, 25);
        printf("Video_CreateVideoFile(\"test.mp4\") = %d \n", iRet);

        iRet = Video_WriteH264Frame(h264Handle, FRAMETYPE_MP4_VIDEO, pData, size);
        printf("Video_WriteH264Frame = %d \n", iRet);

        iRet = Video_CloseVideoFile(h264Handle);
        printf("Video_CloseVideoFile = %d \n", iRet);

        Video_CloseProcessHandle(h264Handle);
        h264Handle = NULL;
    }
    else
    {
        printf("Video_CreateProcessHandle failed. \n");
    }

    if (pData)
    {
        delete[] pData;
        pData = NULL;
    }

	return 0;
}

