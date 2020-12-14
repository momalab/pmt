#include <fstream>
#include <vector>

#include "cons.hpp"
#include "filter.hpp"
#include "efilter.hpp"
#include "etext.hpp"
#include "io.hpp"
#include "text.hpp"

using namespace bloom;
using namespace io;
using namespace std;
using namespace text;

int main()
try {
    auto queries = stosz( split( load( cons::queryfile ), cons::delimiter ) );
    auto params = stosz( split( load( cons::configfile ), cons::delimiter ) );
    auto efilterdata = stoct<SecureMod>( load( cons::randomfilterfile ) );
    EFilter<SZ> filter(params, efilterdata);
    ofstream fout( cons::resultfile );
    for ( auto & query : queries )
        fout << stringfy( filter.queryFast(query), cons::delimiter ) << '\n';
}
catch (const char   * e) { cout << "error: " << e << '\n'; return 1; }
catch (const string & e) { cout << "error: " << e << '\n'; return 1; }
