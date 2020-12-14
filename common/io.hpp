#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace io
{

std::vector<std::string> load(const std::string & filename);
std::string trim(const std::string & sin);

} // io
