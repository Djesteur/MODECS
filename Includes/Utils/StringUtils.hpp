/*
	MODECS - A video game by Guillaume "Djesteur" Fabre
	This software is under CC BY-NC-SA 4.0 license (https://creativecommons.org/licenses/by-nc-sa/4.0/ for more informations)
*/

#ifndef STRINGUTILS_HPP
#define STRINGUTILS_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>

std::vector<std::string> splitDatas(const std::string &datas, const char spliter);
unsigned int convertStringHexToUnsigned(const std::string &hexaString);
std::string getPartOfMessage(std::string &message);

#endif