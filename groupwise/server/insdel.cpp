#include <iostream>
#include <string>
#include <vector>

#include "cons.hpp"
#include "filter.hpp"
#include "efilter.hpp"
#include "etext.hpp"
#include "io.hpp"
#include "text.hpp"
#include "timer.hpp"

using namespace bloom;
using namespace io;
using namespace std;
using namespace text;

int main(int argc, char* argv[])
try
{
    if ( argc < 3 )
    {
        cout << "Inform the command, the entry file, and logp\n";
        cout << "Command: { insert, remove }\n";
        return 1;
    }
    auto cmd = string( argv[1] );
    if ( cmd != "insert" && cmd != "remove" )
    {
        cout << "Invalid command. Use: 'insert' or 'remove'\n";
        return 1;
    }
    auto insert = cmd == "insert";
    cout << "\n" << (insert ? "Insert" : "Remove" ) << '\n';
    auto entryfile = string( argv[2] );
    size_t logp = stoull( argv[3] );
    auto entries = load( entryfile );
    auto orders = stoct<SecureUint<SZ>> ( load( cons::erandomfile ) );
    auto params = stosz ( split( load( cons::configfile ), cons::delimiter ) );
    auto filterdata = stosz( load( cons::filterfile ) );
    auto efilterdata = stoct<SecureMod>( load( cons::randomfilterfile ) );
    EFilter filter(params, filterdata, efilterdata, orders);
    Timer t;
    for ( auto & entry : entries )
    {
        auto indices = filter.hash(entry);
        if ( insert ) filter.insertFast(indices, logp);
        else filter.removeFast(indices, logp);
    }
    auto r  = t.get();
    const unsigned us = 1000000;
    cout << "runtime: " << double(r)/us << " s\n";
    filter.saveFilter( cons::filterfile );
    filter.saveEFilter( cons::randomfilterfile );
    cout << '\n';
}
catch (const char   * e) { cout << "error: " << e << '\n'; return 1; }
catch (const string & e) { cout << "error: " << e << '\n'; return 1; }
