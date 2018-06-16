#include "Utils/StringUtils.hpp"

std::vector<std::string> splitDatas(const std::string &datas, const char spliter) {

	std::stringstream ss{datas};
    std::string currentData;
    std::vector<std::string> splited;

    while (std::getline(ss, currentData, spliter)) { splited.push_back(currentData); }

    return splited;
}

unsigned int convertStringHexToUnsigned(const std::string &hexaString) {

	unsigned int result{0};

	std::istringstream iss{hexaString};
	iss >> std::setbase(16) >> result;

	return result;
}