#pragma once

#include <vector>
#include "e3int.h"
#include "math.hpp"

namespace math
{

template <int SZ> SecureMod
eqmul( const SecureUint<SZ> & c, size_t p, const SecureMod & m)
{
    std::vector<SecureMod> r(1, m);
    for ( size_t i=0; i<SZ; i++ )
        r.push_back( SecureMod( (p>>i)&1 ? c[i].native() : SecureBit::gate_not(c[i]).native() ) );
    return mul_vector(r);
}

template <int SZ> SecureMod
equal( const SecureUint<SZ> & c, size_t p)
{
    std::vector<SecureMod> r;
    for ( size_t i=0; i<SZ; i++ )
        r.push_back( SecureMod( (p>>i)&1 ? c[i].native() : SecureBit::gate_not(c[i]).native() ) );
    return mul_vector(r);
}

} // math
