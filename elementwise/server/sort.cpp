#include <iostream>

#include "cons.hpp"
#include "efilter.hpp"
#include "etext.hpp"
#include "filter.hpp"
#include "io.hpp"
#include "text.hpp"
#include "timer.hpp"

using namespace bloom;
using namespace io;
using namespace std;
using namespace text;

int main()
try {
    cout << "\nSort\n";
    auto order = stoct<SecureUint<SZ>>( load( cons::erandomfile ) );
    auto params = stosz ( split( load( cons::configfile ), cons::delimiter ) );
    auto filterdata = stosz ( load( cons::filterfile ) );
    EFilter filter(params, filterdata, order);
    Timer t;
    filter.sort();
    auto r  = t.get();
    const unsigned us = 1000000;
    cout << "runtime: " << double(r)/us << " s\n";
    filter.saveEFilter( cons::randomfilterfile );
    cout << "# ct-ct muls " << EFilter<SZ>::nMulsC << '\n';
    cout << "# ct-pt muls " << EFilter<SZ>::nMulsP << '\n';
    cout << "\n";
}
catch (const char   * e) { cout << "error: " << e << '\n'; return 1; }
catch (const string & e) { cout << "error: " << e << '\n'; return 1; }
