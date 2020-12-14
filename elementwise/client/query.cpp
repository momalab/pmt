#include <fstream>
#include <iostream>
#include <string>

#include "cons.hpp"
#include "filter.hpp"
#include "io.hpp"
#include "text.hpp"

using namespace bloom;
using namespace io;
using namespace std;
using namespace text;

int main(int argc, char* argv[])
try {
    if ( argc <  2 )
    {
        cout << "Inform the query file\n";
        return 1;
    }
    auto queryfile = string( argv[1] );
    auto queries = load(queryfile);
    auto orders = stosz( load( cons::randomfile ) );
    auto params = stosz( split( load( cons::configfile ), cons::delimiter ) );
    Filter filter(params);
    ofstream fout( cons::queryfile );
    for ( auto & query : queries )
    {
        auto hashes = filter.hash(query);
        string output = "";
        for ( auto & hash : hashes )
        {
            auto it = find( orders.begin(), orders.end(), hash );
            size_t pos = distance( orders.begin(), it );
            output += to_string(pos) + cons::delimiter;
        }
        fout << output.substr( 0, output.size()-1 ) << '\n';
    }
}
catch (const char   * e) { cout << "error: " << e << '\n'; return 1; }
catch (const string & e) { cout << "error: " << e << '\n'; return 1; }
