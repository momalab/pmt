#include <algorithm>
#include <iostream>
#include <string>
#include "e3int.h"
#include "e3key.h"

#include "cons.hpp"
#include "etext.hpp"
#include "io.hpp"
#include "text.hpp"
#include "timer.hpp"

using namespace io;
using namespace std;
using namespace text;

int main(int argc, char* argv[])
try {
    if ( argc < 3 )
    {
        cout << "Inform the query file, logp\n";
        return 1;
    }
    cout << "\nQUERY\n";
    auto queryfile = string( argv[1] );
    size_t logp = stoull( argv[2] );
    auto queries = load( queryfile );
    auto orders = stosz( load( cons::randomfile ) );
    auto indices = stosz( split( load( cons::localqueryfile ), cons::delimiter ) );
    auto eresults = stoct<SecureMod>( split( load( cons::resultfile ), cons::delimiter ) );
    auto n = SecureMod::slots();
    auto np = n * logp;
    auto s = orders.size(); // m / np + (m % np > 0);
    Timer t;
    for ( size_t i=0; i<queries.size(); i++ )
    {
        bool contains = true;
        for ( size_t j=0; j<eresults[i].size(); j++ )
        {
            auto vstr = split( e3::decrypt( eresults[i][j] ), '_' );
            auto & last = vstr.back();
            auto len = last.size();
            if ( len > 3 && last.substr(len-3, len) == "..." )
                last = last.substr(0, len-3);
            vstr.resize(n, last);
            auto v = stosz( vstr );
            auto & idx = indices[i][j];
            auto x = ( idx - (idx % s) ) / s;
            auto pos = x / logp;
            auto bit = logp-1 - (x % logp);
            contains = ( v[pos] >> bit ) & 1;
            if ( !contains ) break;
        }
        cout << "The database " << ( contains ? "contains" : "does not contain" );
        cout << " the entry " << queries[i] << '\n';
    }
    auto r  = t.get();
    const unsigned us = 1000000;
    cout << "runtime: " << double(r)/us << " s\n";
    cout << '\n';
}
catch (const char   * e) { cout << "error: " << e << '\n'; return 1; }
catch (const string & e) { cout << "error: " << e << '\n'; return 1; }
