#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <windows.h>
#include <shellapi.h>
#include <memory>
#include "STRING.hpp"

std::unordered_map<STRING, std::vector<STRING>> argParse(std::unordered_map<STRING, STRING> optionDict);
std::unordered_map<STRING, std::vector<STRING>> argParse(std::vector<STRING> optionList);
std::vector<STRING> getArgs();
std::vector<int> castInt(std::vector<STRING> &strVec);
std::vector<bool> castBool(std::vector<STRING> &strVec);