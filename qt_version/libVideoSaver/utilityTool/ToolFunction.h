#ifndef TOOL_FUNCTION_H
#define TOOL_FUNCTION_H
#include <iostream>

#define OUT_LOG(fmt,...) Tool_WriteFormatLog_video("%s:: " fmt, __FUNCTION__, ##__VA_ARGS__);

//************************************
// Method:        Tool_ReplaceStringInStd
// Describe:        �����滻ָ���ַ����������滻���ַ�Ϊ�գ���ɾ����ָ���ַ���
// FullName:      Tool_ReplaceStringInStd
// Access:          public 
// Returns:        std::string
// Returns Describe:
// Parameter:    std::string strOrigin
// Parameter:    std::string strToReplace
// Parameter:    std::string strNewChar
//************************************
std::string Tool_ReplaceStringInStd_video(std::string strOrigin, std::string strToReplace, std::string strNewChar);

void Tool_WriteFormatLog_video(const char* szfmt, ...);

#endif
