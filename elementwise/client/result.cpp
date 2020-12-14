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
    if ( argc < 2 )
    {
        cout << "Inform the query file\n";
        return 1;
    }
    cout << "\nQUERY\n";
    auto queryfile = string( argv[1] );
    auto queries = load( queryfile );
    auto indices = stosz( split( load( cons::queryfile ), cons::delimiter ) );
    auto eresults = stoct<SecureMod>( split( load( cons::resultfile ), cons::delimiter ) );
    auto slots = SecureMod::slots();
    Timer t;
    for ( size_t i=0; i<queries.size(); i++ )
    {
        bool contains = true;
        for ( size_t j=0; j<eresults[i].size(); j++ )
        {
            auto e = e3::decrypt( eresults[i][j] );
            auto l = e.size();
            if ( l > 3 && e.substr(l-3, l) == "..." ) e = e.substr(0,l-3);
            auto & idx = indices[i][j];
            auto v = split(e, '_');
            v.resize( slots, v.back() );
            if ( v[idx % slots] == "0" )
            {
                contains = false;
                break;
            }
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
