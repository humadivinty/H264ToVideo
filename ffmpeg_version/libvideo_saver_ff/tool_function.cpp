#include "Tool_function.h"
#include <stdio.h>
#include <chrono>
#include <stdarg.h>
#include <memory.h>

namespace video_saver_ffmpeg
{
#define DLL_VERSION "1.0.0.1"

void tool_ReadFileAll(char* filename, char** data, long* len)
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

void Tool_getDateTimeWithMillisecond(DateTimeWithMilsec& timeStruct)
{
    auto now = std::chrono::system_clock::now();
    time_t in_time_t = std::chrono::system_clock::to_time_t(now);
    struct tm* ptmNow = localtime(&in_time_t);

    auto duration = now.time_since_epoch();
    long long  iMillisecond = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    timeStruct.year = ptmNow->tm_year + 1900;
    timeStruct.month = ptmNow->tm_mon + 1;
    timeStruct.day = ptmNow->tm_mday;
    timeStruct.hour = ptmNow->tm_hour;
    timeStruct.minute = ptmNow->tm_min;
    timeStruct.second = ptmNow->tm_sec;
    timeStruct.millisecond = static_cast<int>(iMillisecond % 1000);
}

void tool_writeFormatLog(const char *szfmt, ...)
{
#ifdef ENABLE_LOG
    char chLogBuf[1024] = {0};
    memset(chLogBuf, 0, sizeof(chLogBuf));

    va_list arg_ptr;
    va_start(arg_ptr, szfmt);
    vsnprintf(chLogBuf, sizeof(chLogBuf), szfmt, arg_ptr);
    va_end(arg_ptr);

    DateTimeWithMilsec timeStruct;
    Tool_getDateTimeWithMillisecond(timeStruct);

    fprintf(stderr, "[%04d-%02d-%02d %02d:%02d:%02d.%03d][%s] %s\n",
        timeStruct.year,
        timeStruct.month,
        timeStruct.day,
        timeStruct.hour,
        timeStruct.minute,
        timeStruct.second,
        timeStruct.millisecond,
        DLL_VERSION,
        chLogBuf);
#endif
}


}
