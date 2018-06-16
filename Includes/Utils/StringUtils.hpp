#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

std::vector<std::string> splitDatas(const std::string &datas, const char spliter);
unsigned int convertStringHexToUnsigned(const std::string &hexaString);

#endif