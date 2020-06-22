#include "ToolFunction.h"

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
