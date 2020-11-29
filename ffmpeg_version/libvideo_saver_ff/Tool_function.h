#ifndef TOOL_FUNCTION_H
#define TOOL_FUNCTION_H

namespace video_saver_ffmpeg
{

#define OUT_LOG(fmt,...) fprintf(stderr, "%s:: " fmt "\n", __FUNCTION__, ##__VA_ARGS__);

void tool_ReadFileAll(char* filename, char** data, long* len);

}



#endif // tool_function_h
