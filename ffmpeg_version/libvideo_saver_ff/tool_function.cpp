#include "Tool_function.h"
#include <stdio.h>
namespace video_saver_ffmpeg
{

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


}
