#ifndef TOOL_FUNCTION_H
#define TOOL_FUNCTION_H
#include <iostream>

#define PRINT_INFO(fmt, ...)  Tool_PrintfInfo("%s:: " fmt,  __FUNCTION__,##__VA_ARGS__);


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
std::string Tool_ReplaceStringInStd(std::string strOrigin, std::string strToReplace, std::string strNewChar);

void Tool_PrintfInfo(const char* szfmt, ...);

#endif