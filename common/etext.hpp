#pragma once

#include <string>
#include <vector>
#include "e3int.h"

namespace text
{

template <class T> std::vector<T>
stoct(const std::vector<std::string> & v)
{
    std::vector<T> vout;
    for ( const auto & e : v ) vout.push_back( T(e) );
    return vout;
}

template <class T> std::vector<std::vector<T>>
stoct(const std::vector<std::vector<std::string>> & v)
{
    std::vector<std::vector<T>> vout;
    for ( const auto & e : v ) vout.push_back( stoct<T>(e) );
    return vout;
}

template <class T> std::string
stringfy(const std::vector<T> & v, char delimiter)
{
    string output = "";
    for ( const auto & e : v ) output += e.str() + delimiter;
    if ( !output.empty() ) output = output.substr( 0, output.size()-1 );
    return output;
}

} // text
