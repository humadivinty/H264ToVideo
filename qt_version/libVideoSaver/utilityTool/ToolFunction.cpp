#include "ToolFunction.h"
#include <stdarg.h>
#include<memory.h>
#include<stdio.h>

std::string Tool_ReplaceStringInStd_video(std::string strOrigin, std::string strToReplace, std::string strNewChar)
{
    std::string strFinal = strOrigin;
    if (strFinal.empty())
    {
        return strFinal;
    }

    if (strNewChar.empty())
    {
        size_t pos = std::string::npos;

        // Search for the substring in string in a loop untill nothing is found
        while ((pos = strFinal.find(strToReplace)) != std::string::npos)
        {
            // If found then erase it from string
            strFinal.erase(pos, strToReplace.length());
        }
    }
    else
    {
        for (std::string::size_type pos(0); pos != std::string::npos; pos += strNewChar.length())
        {
            pos = strFinal.find(strToReplace, pos);
            if (pos != std::string::npos)
                strFinal.replace(pos, strToReplace.length(), strNewChar);
            else
                break;
        }
    }
    return   strFinal;
}

void Tool_WriteFormatLog_video(const char *szfmt, ...)
{
#ifdef OUTPUT_LOG
    char g_szPbString[10240] = { 0 };
    memset(g_szPbString, 0, sizeof(g_szPbString));

    va_list arg_ptr;
    va_start(arg_ptr, szfmt);
    vsnprintf(g_szPbString, sizeof(g_szPbString), szfmt, arg_ptr);
    va_end(arg_ptr);

    printf("%s\n", g_szPbString);
#endif
}
