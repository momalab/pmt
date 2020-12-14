#include <algorithm>
#include <fstream>

#include "io.hpp"

using namespace std;

namespace io
{

vector<string> load(const string & filename)
{
    ifstream fin(filename);
    vector<string> lines;
    string line;
    while ( getline(fin, line) ) lines.push_back( trim(line) );
    return lines;
}

string trim(const string & sin)
{
    string s = sin;
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

} // io
