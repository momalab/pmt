#include <iostream>
#include <string>

#include "cons.hpp"
#include "filter.hpp"
#include "io.hpp"

using namespace bloom;
using namespace io;
using namespace std;

int main(int argc, char *argv[])
try {
    if ( argc < 4 )
    {
        cout << "Inform the database filename, bloom filter size, # hashes\n";
        return 1;
    }

    auto dbname = string( argv[1] );
    size_t m = stoull( argv[2] );
    size_t h = stoull( argv[3] );
    auto database = load(dbname);

    Filter filter(m, h);
    filter.insert(database);
    filter.save( cons::configfile, cons::filterfile );

    cout << "Non-zero flags: " << filter.count() << '\n';
}
catch (const char   * e) { cout << "error: " << e << '\n'; return 1; }
catch (const string & e) { cout << "error: " << e << '\n'; return 1; }
