#ifndef TOOL_FUNCTION_H
#define TOOL_FUNCTION_H
#include <iostream>

//************************************
// Method:        Tool_ReplaceStringInStd
// Describe:        用于替换指定字符串，若被替换的字符为空，则删除该指定字符串
// FullName:      Tool_ReplaceStringInStd
// Access:          public 
// Returns:        std::string
// Returns Describe:
// Parameter:    std::string strOrigin
// Parameter:    std::string strToReplace
// Parameter:    std::string strNewChar
//************************************
std::string Tool_ReplaceStringInStd(std::string strOrigin, std::string strToReplace, std::string strNewChar);

#endif