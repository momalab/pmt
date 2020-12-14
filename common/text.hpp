#pragma once

#include <string>
#include <vector>

namespace text
{

std::vector<std::string> split(const std::string & s, char delimiter);
std::vector<std::vector<std::string>> split(const std::vector<std::string> & v, char delimiter);
std::vector<size_t> stosz(const std::vector<std::string> & v);
std::vector<std::vector<size_t>> stosz(const std::vector<std::vector<std::string>> & v);
std::string stringfy(const std::vector<size_t> & v, char delimiter);

} // text
