#include "argparse.hpp"

std::vector<STRING> getArgs()
{
    std::vector<STRING> argList;
    STRING arg;
    char *pMBBuffer;
    size_t dummy;
    LPWSTR *szArglist;
    int nArgs;

    pMBBuffer = new char[MAX_PATH];
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    for (int i = 0; i < nArgs; i++)
    {
#ifdef UNICODE
        arg = new STRING(szArglist[i]);
#else
        wcstombs_s(&dummy, pMBBuffer, (size_t)MAX_PATH, szArglist[i], (size_t)MAX_PATH - 1);
        arg = std::string(pMBBuffer);
#endif
        argList.push_back(arg);
    }
    delete pMBBuffer;
    LocalFree(szArglist);
    return argList;
}

std::unordered_map<STRING, std::vector<STRING>> argParse(std::unordered_map<STRING, STRING> optionDict)
{
    std::vector<STRING> argList = getArgs();
    std::unordered_map<STRING, std::vector<STRING>> returnDict;
    std::pair<STRING, std::vector<STRING>> keyValue;
    for (auto option : optionDict)
    {
        keyValue = std::pair<STRING, std::vector<STRING>>(option.first, std::vector<STRING>());
        returnDict.insert(std::move(keyValue));
    }

    std::vector<STRING>::iterator optionItr;
    STRING optionName;
    for (int i = 0; i < (int)argList.size(); ++i)
    {
        if (optionDict.find(argList[i]) != optionDict.end())
        {
            optionName = argList[i];
            while (optionDict.find(argList[++i]) == optionDict.end())
            {
                returnDict.at(optionName).push_back(argList[i]);
                if (i >= (int)argList.size() - 1)
                    break;
            }
            i--;
        }
    }
    for (auto itr = returnDict.begin(); itr != returnDict.end(); ++itr)
        if (itr->second.size() == 0)
            itr->second.push_back(optionDict.at(itr->first));

    return returnDict;
}

std::unordered_map<STRING, std::vector<STRING>> argParse(std::vector<STRING> optionList)
{
    std::vector<STRING> argList = getArgs();
    std::unordered_map<STRING, std::vector<STRING>> returnDict;
    std::pair<STRING, std::vector<STRING>> keyValue;
    for (auto i : optionList)
    {
        keyValue = std::pair<STRING, std::vector<STRING>>(i, std::vector<STRING>());
        returnDict.insert(std::move(keyValue));
    }

    std::vector<STRING>::iterator optionItr;
    STRING optionName;
    for (int i = 0; i < (int)argList.size(); ++i)
    {
        if (std::find(optionList.begin(), optionList.end(), argList[i]) != optionList.end())
        {
            optionName = argList[i];
            while (std::find(optionList.begin(), optionList.end(), argList[++i]) == optionList.end())
            {
                returnDict.at(optionName).push_back(argList[i]);
                if (i >= (int)argList.size() - 1)
                    break;
            }
            i--;
        }
    }
    return returnDict;
}

std::vector<int> castInt(std::vector<STRING> &strVec)
{
    std::vector<int> returnVec;
    for (auto item : strVec)
        returnVec.push_back(std::stoi(item));
    return returnVec;
}

std::vector<bool> castBool(std::vector<STRING> &strVec)
{
    std::vector<bool> returnVec;
    for (auto item : strVec)
        returnVec.push_back((item == TEXT("true")) ? true : false);
    return returnVec;
}