#include <algorithm>
#include <fstream>

#include "filter.hpp"

using namespace std;

namespace bloom
{

Filter::Filter(size_t m, size_t h)
{
    for ( size_t i=0; i<h; i++ )
        hashes.push_back( Hash(rand(), m) );
    filter.resize(m, 0);
}

Filter::Filter(const vector<Hash> & hashes, const vector<size_t> & filter )
{
    size_t m = 0;
    this->filter.assign( filter.begin(), filter.end() );
    for ( const auto & hash : hashes )
    {
        this->hashes.push_back(hash);
        auto mod = hash.getModulus();
        m = mod>m ? mod : m;
    }
    this->filter.resize(m, 0);
}

Filter::Filter(const vector<vector<size_t>> params, const vector<size_t> & filter )
{
    vector<Hash> hashes;
    for ( auto & p : params ) hashes.push_back( Hash(p[0], p[1]) );
    *this = Filter(hashes, filter);
}

bool Filter::contains(const string & data)
{   return contains( hash(data) );  }

bool Filter::contains(const vector<size_t> & indices)
{
    for ( auto idx : indices )
        if ( !filter[idx] ) return false;
    return true;
}

size_t Filter::count()
{
    return count_if( filter.begin(), filter.end(), [](size_t e){return e;} );
}

vector<size_t> Filter::hash(const string & data)
{
    vector<size_t> v;
    for ( const auto & hash : hashes ) v.push_back( hash.hash(data) );
    return v;
}

vector< pair<size_t,size_t> > Filter::insert(const string & data)
{   return insert( hash(data) );    }

vector<vector< pair<size_t,size_t> >> Filter::insert(const vector<string> & database)
{
    vector<vector< pair<size_t,size_t> >> pairs;
    for ( const auto & data : database ) pairs.push_back( insert(data) );
    return pairs;
}

vector< pair<size_t,size_t> > Filter::insert(const vector<size_t> & indices)
{
    vector< pair<size_t,size_t> > pairs;
    for ( const auto & idx : indices )
    {
        pair<size_t,size_t> p;
        p.first = idx;
        p.second = ++filter[idx];
        pairs.push_back(p);
    }
    return pairs;
}

vector<size_t> Filter::query(const string & data)
{    return query( hash(data) );    }

vector<size_t> Filter::query(const vector<size_t> & indices)
{
    vector<size_t> values;
    for ( auto & idx : indices ) values.push_back( filter[idx] );
    return values;
}

vector< pair<size_t,size_t> > Filter::remove(const string & data)
{   return remove( hash(data) );    }

vector< pair<size_t,size_t> > Filter::remove(const vector<size_t> & indices)
{
    vector< pair<size_t,size_t> > pairs;
    for ( const auto & idx : indices )
    {
        pair<size_t,size_t> p;
        p.first = idx;
        filter[idx] -= filter[idx] > 0;
        p.second = filter[idx];
        pairs.push_back(p);
    }
    return pairs;
}

bool Filter::save(const string & configname, const string & filtername)
{    return saveConfig(configname) && saveFilter(filtername);   }

bool Filter::saveConfig(const string & configname)
{
    try
    {
        ofstream fout(configname);
        for ( const auto & hash : hashes ) fout << hash << '\n';
    }
    catch (...) { return false; }
    return true;
}

bool Filter::saveFilter(const string & filtername)
{
    try
    {
        ofstream fout(filtername);
        for ( auto e : filter ) fout << e << '\n';
    }
    catch (...) { return false; }
    return true;
}

size_t Filter::size() { return filter.size(); }

void Filter::sort(const vector<size_t> & order)
{
    vector<size_t> reorderedFilter;
    for ( auto idx : order )
        reorderedFilter.push_back( filter[idx] );
    filter = reorderedFilter;
}

ostream & operator<<(ostream & os, const Hash & hash)
{
    os << hash.seed << ' ' << hash.mod;
    return os;
}

} // bloom
