#pragma once

#include <vector>

namespace math
{

size_t sizeCeilPowerOfTwo(size_t n)
{
    size_t counter=0;
    while (n)
    {
        counter++;
        n>>=1;
    }
    return counter;
}

template <class T>
T add_vector(std::vector<T> & v)
{
    auto size = v.size();
    if ( !size ) return T( (unsigned long long)(0) );
    for ( auto n = 1<<sizeCeilPowerOfTwo(size); n>1; )
    {
        n >>= 1;
        for ( size_t i=n; i<size; i++ ) v[i-n] += v[i];
        size = n;
    }
    return v[0];
}

template <class T>
T mul_vector(std::vector<T> & v)
{
    auto size = v.size();
    for ( auto n = 1<<sizeCeilPowerOfTwo(size); n>1; )
    {
        n >>= 1;
        for ( size_t i=n; i<size; i++ ) v[i-n] *= v[i];
        size = n;
    }
    return v[0];
}

} // math
