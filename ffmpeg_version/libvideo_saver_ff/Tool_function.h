#ifndef TOOL_FUNCTION_H
#define TOOL_FUNCTION_H

namespace video_saver_ffmpeg
{
typedef struct
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int millisecond;
}DateTimeWithMilsec;

void Tool_getDateTimeWithMillisecond(DateTimeWithMilsec& timeStruct);

void tool_writeFormatLog(const char* szfmt, ...);

void tool_ReadFileAll(char* filename, char** data, long* len);

#define OUT_LOG(fmt,...) tool_writeFormatLog("%s:: " fmt , __FUNCTION__, ##__VA_ARGS__);
}



#endif // tool_function_h
