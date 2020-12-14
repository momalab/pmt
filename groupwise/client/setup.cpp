#include <algorithm>
#include <fstream>
#include <random>
#include <vector>
#include "e3int.h"

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
    if ( argc < 2 )
    {
        cout << "Inform logp\n";
        return 1;
    }
    auto logp = stoull( argv[1] );

    auto slots = SecureMod::slots();
    std::cout << "SLOTS: " << slots << '\n';
    auto params = stosz( split( load( cons::configfile ), cons::delimiter ) );
    Filter filter(params);
    auto size = filter.size();
    auto sp = slots * logp;
    size = ( size / sp ) + (size % sp > 0);
    vector<size_t> order;
    for ( size_t i=0; i<size; i++ ) order.push_back(i);
    auto rd = random_device{};
    auto rng = default_random_engine{ rd() };
    shuffle( order.begin(), order.end(), rng );
    ofstream fout( cons::randomfile );
    ofstream gout( cons::erandomfile );
    for ( size_t i=0; i<order.size(); i++ )
    {
        auto n = order[i];
        vector<unsigned long long> indices(slots, n);
        fout << n << '\n';
        gout << SecureUint<SZ>(indices) << '\n';
    }
}
catch (const char   * e) { cout << "error: " << e << '\n'; return 1; }
catch (const string & e) { cout << "error: " << e << '\n'; return 1; }
