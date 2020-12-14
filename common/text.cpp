#include "text.hpp"

using namespace std;

namespace text
{

vector<string> split(const string & s, char delimiter)
{
    vector<string> v;
    string item = "";
    for ( auto & c : s )
    {
        if ( c == delimiter )
        {
            v.push_back(item);
            item = "";
        }
        else item += c;
    }
    v.push_back(item);
    return v;
}

vector<vector<string>> split(const vector<string> & v, char delimiter)
{
    vector<vector<string>> m;
    for ( const auto & s : v ) m.push_back( split(s, delimiter) );
    return m;
}

vector<size_t> stosz(const vector<string> & v)
{
    vector<size_t> vout;
    for ( const auto & e : v ) vout.push_back( stoull(e) );
    return vout;
}

vector<vector<size_t>> stosz(const vector<vector<string>> & v)
{
    vector<vector<size_t>> vout;
    for ( const auto & e : v ) vout.push_back( stosz(e) );
    return vout;
}

string stringfy(const vector<size_t> & v, char delimiter)
{
    string output = "";
    for ( const auto & e : v ) output += to_string(e) + delimiter;
    if ( !output.empty() ) output = output.substr( 0, output.size()-1 );
    return output;
}

} // text
