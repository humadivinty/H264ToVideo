#include "stdafx.h"
#include "ToolFunction.h"
#include <memory.h>
#include <stdarg.h>

std::string Tool_ReplaceStringInStd(std::string strOrigin, std::string strToReplace, std::string strNewChar)
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

void Tool_PrintfInfo(const char* szfmt, ...)
{
#ifdef OUTPUT_INFO
	char m_chLogBuf[1024] = {0};
	memset(m_chLogBuf, 0, sizeof(m_chLogBuf));

	va_list arg_ptr;
	va_start(arg_ptr, szfmt);
	vsnprintf(m_chLogBuf, sizeof(m_chLogBuf), szfmt, arg_ptr);
	va_end(arg_ptr);

	printf("%s\n", m_chLogBuf);
#endif
}