#include <iostream>
#include<string>
#include <stdio.h>
#include "libvideo_saver/libvideo_saver_ff.h"
using namespace std;

void tool_ReadFile(const char* filename, char** data, long* len)
{
    FILE* pf = fopen(filename, "rb");
    if (pf == NULL)
    {
        printf("filename err\n");
        return;
    }
    fseek(pf, 0, SEEK_END);
    *len = ftell(pf);
    char* temp = new char[*len + 1];
    rewind(pf);
    fread(temp, sizeof(char), *len, pf);
    temp[*len] = '\0';
    *data = temp;
    fclose(pf);
    pf = NULL;
}

int main(int argc, char *argv[])
{
    cout << "Hello World!" << endl;
    if (argc < 3)
    {
        cout << "please put the input video file path." << endl;
        return 0;
    }

    std::string strInputFileName(argv[1]);
    std::string strOutputFileName(argv[2]);

    char * pVideoData = NULL;
    long iVideoLength = 0;

    tool_ReadFile(strInputFileName.c_str(), &pVideoData, &iVideoLength);
    if(pVideoData == NULL || iVideoLength == 0)
    {
        cout<<"read video file failed."<<endl;
    }

    void* processHandle = Video_CreateProcessHandle();
    if(NULL == processHandle)
    {
        cout<<"Video_CreateProcessHandle failed."<<endl;
    }
    int iRet = Video_CreateVideoFile(processHandle, strOutputFileName.c_str(),1920,1080, 25);
    cout<< "Video_CreateVideoFile " << strOutputFileName<< " =" << iRet<<endl;
    printf("pf Video_CreateVideoFile = %d \n", iRet);

    iRet = Video_WriteH264Frame(processHandle, 1, (unsigned char*) pVideoData, iVideoLength);
    cout<< "Video_WriteH264Frame  = " << iRet <<endl;
    printf("pf Video_WriteH264Frame = %d \n", iRet);

     iRet = Video_CloseVideoFile(processHandle);
     cout<< "Video_CloseVideoFile  = " << iRet<<endl;
      printf("pf Video_CloseVideoFile = %d \n", iRet);

     iRet = Video_CloseProcessHandle(processHandle);
     cout<< "Video_CloseProcessHandle  = " << iRet<<endl;
     printf("pf Video_CloseProcessHandle = %d \n", iRet);

    return 0;
}
