#pragma once

#include <algorithm>
#include <fstream>

#include "e3int.h"
#include "filter.hpp"
#include "math.hpp"
#include "emath.hpp"

namespace bloom
{

template <int SZ>
class EFilter : Filter
{
    private:
        std::vector<SecureMod> efilter;
        std::vector<SecureUint<SZ>> order;

    public:
        static size_t nMulsC;
        static size_t nMulsP;

    public:
        EFilter() {}
        EFilter(const std::vector<Hash> & hashes,
            const std::vector<size_t> & filter,
            const std::vector<SecureMod> & efilter,
            const std::vector<SecureUint<SZ>> & order);
        EFilter(const std::vector<std::vector<size_t>> params,
            const std::vector<size_t> & filter,
            const std::vector<SecureMod> & efilter,
            const std::vector<SecureUint<SZ>> & order);
        EFilter(const std::vector<std::vector<size_t>> params,
            const std::vector<size_t> & filter,
            const std::vector<SecureUint<SZ>> & order)
            : EFilter(params, filter, std::vector<SecureMod>(), order) {}
        EFilter(const std::vector<std::vector<size_t>> params,
            const std::vector<size_t> & filter,
            const std::vector<SecureMod> & efilter)
            : EFilter(params, filter, efilter, std::vector<SecureUint<SZ>>()) {}
        EFilter(const std::vector<std::vector<size_t>> params,
            const std::vector<SecureMod> & efilter)
            : EFilter(params, std::vector<size_t>(), efilter) {}

        std::vector<size_t> hash(const std::string & data);
        void insert(const std::string & data);
        void insert(const std::vector<size_t> & indices);
        void insertFast(const std::string & data, size_t logp);
        void insertFast(const std::vector<size_t> & indices, size_t logp);
        std::vector<SecureMod> query(const std::vector<size_t> & indices);
        std::vector<SecureMod> queryFast(const std::vector<size_t> & indices);
        void remove(const std::string & data);
        void remove(const std::vector<size_t> & indices);
        void removeFast(const std::string & data, size_t logp);
        void removeFast(const std::vector<size_t> & indices, size_t logp);
        bool saveEFilter(const std::string & filtername);
        bool saveFilter(const std::string & filtername);
        void sort();
        void sortFast(size_t logp);
};

template <int SZ> size_t EFilter<SZ>::nMulsC = 0;
template <int SZ> size_t EFilter<SZ>::nMulsP = 0;

template <int SZ>
EFilter<SZ>::EFilter(const std::vector<Hash> & hashes,
    const std::vector<size_t> & filter,
    const std::vector<SecureMod> & efilter,
    const std::vector<SecureUint<SZ>> & order)
{
    this->hashes.assign( hashes.begin(), hashes.end() );
    this->filter.assign( filter.begin(), filter.end() );
    this->efilter.assign( efilter.begin(), efilter.end() );
    this->order.assign( order.begin(), order.end() );
}

template <int SZ>
EFilter<SZ>::EFilter(const std::vector<std::vector<size_t>> params,
    const std::vector<size_t> & filter,
    const std::vector<SecureMod> & efilter,
    const std::vector<SecureUint<SZ>> & order)
{
    std::vector<Hash> hashes;
    for ( auto & p : params ) hashes.push_back( Hash(p[0], p[1]) );
    *this = EFilter(hashes, filter, efilter, order);
}

template <int SZ> std::vector<size_t>
EFilter<SZ>::hash(const string & data)
{
    std::vector<size_t> v;
    for ( const auto & hash : hashes ) v.push_back( hash.hash(data) );
    return v;
}

template <int SZ> void
EFilter<SZ>::insert(const std::string & data)
{   return insert( hash(data) );    }

template <int SZ> void
EFilter<SZ>::insert(const std::vector<size_t> & indices)
{
    if ( filter.empty() ) throw "Filter cannot be empty";
    if ( efilter.empty() ) throw "Encrypted filter cannot be empty";
    if ( order.empty() ) throw "Order vector cannot be empty";

    for ( const auto & idx : indices )
    {
        if ( !filter[idx]++ )
        {
            for ( size_t i=0; i<efilter.size(); i++ )
            {
                auto eq = math::equal(order[i], idx);
                efilter[i] += eq;
            }
        }
    }
}

template <int SZ> void
EFilter<SZ>::insertFast(const std::string & data, size_t logp)
{   return insertFast( hash(data), logp );    }

template <int SZ> void
EFilter<SZ>::insertFast(const std::vector<size_t> & indices, size_t logp)
{
    if ( filter.empty() ) throw "Filter cannot be empty";
    if ( efilter.empty() ) throw "Encrypted filter cannot be empty";
    if ( order.empty() ) throw "Order vector cannot be empty";

    auto n = SecureMod::slots();
    auto s = order.size();
    for ( const auto & idx : indices )
    {
        if ( !filter[idx]++ )
        {
            std::vector<unsigned long long> mask(n, 0);
            auto x = ( idx - (idx % s) ) / s;
            auto pos = x / logp;
            auto bit = logp-1 - (x % logp);
            unsigned long long value = 1 << bit;
            mask[pos] = value;
            auto jdx = idx % s;
            for ( size_t i=0; i<efilter.size(); i++ )
            {
                auto eq = math::equal(order[i], jdx);
                efilter[i] += eq * mask;
            }
        }
    }
}

template <int SZ> std::vector<SecureMod>
EFilter<SZ>::query(const std::vector<size_t> & indices)
{
    std::vector<SecureMod> values;
    auto slots = SecureMod::slots();
    for ( auto & idx : indices ) values.push_back( efilter[idx / slots] );
    return values;
}

template <int SZ> std::vector<SecureMod>
EFilter<SZ>::queryFast(const std::vector<size_t> & indices)
{
    std::vector<SecureMod> values;
    auto slots = SecureMod::slots();
    for ( auto & idx : indices ) values.push_back( efilter[idx] );
    return values;
}

template <int SZ> void
EFilter<SZ>::remove(const std::string & data)
{   return remove( hash(data) );    }

template <int SZ> void
EFilter<SZ>::remove(const std::vector<size_t> & indices)
{
    if ( filter.empty() ) throw "Filter cannot be empty";
    if ( efilter.empty() ) throw "Encrypted filter cannot be empty";
    if ( order.empty() ) throw "Order vector cannot be empty";

    auto one = SecureMod(1);

    for ( const auto & idx : indices )
    {
        bool cond = filter[idx] > 0;
        filter[idx] -= cond;
        if ( !filter[idx] && cond )
        {
            for ( size_t i=0; i<efilter.size(); i++ )
            {
                auto ne = one - math::equal(order[i], idx);
                efilter[i] *= ne;
            }
        }
    }
}

template <int SZ> void
EFilter<SZ>::removeFast(const std::string & data, size_t logp)
{   return removeFast( hash(data), logp );    }

template <int SZ> void
EFilter<SZ>::removeFast(const std::vector<size_t> & indices, size_t logp)
{
    if ( filter.empty() ) throw "Filter cannot be empty";
    if ( efilter.empty() ) throw "Encrypted filter cannot be empty";
    if ( order.empty() ) throw "Order vector cannot be empty";

    auto n = SecureMod::slots();
    auto s = order.size();
    for ( const auto & idx : indices )
    {
        bool cond = filter[idx] > 0;
        filter[idx] -= cond;
        if ( !filter[idx] && cond )
        {
            std::vector<unsigned long long> mask(n, 0);
            auto x = ( idx - (idx % s) ) / s;
            auto pos = x / logp;
            auto bit = logp-1 - (x % logp);
            unsigned long long value = 1 << bit;
            mask[pos] = value;
            auto jdx = idx % s;
            for ( size_t i=0; i<efilter.size(); i++ )
                efilter[i] -= math::equal(order[i], jdx) * mask;
        }
    }
}

template <int SZ> bool
EFilter<SZ>::saveEFilter(const std::string & filtername)
{
    try
    {
        std::ofstream fout(filtername);
        for ( auto e : efilter ) fout << e << '\n';
    }
    catch (...) { return false; }
    return true;
}

template <int SZ> bool
EFilter<SZ>::saveFilter(const std::string & filtername)
{
    try
    {
        std::ofstream fout(filtername);
        for ( auto e : filter ) fout << e << '\n';
    }
    catch (...) { return false; }
    return true;
}

template <int SZ> void
EFilter<SZ>::sort()
{
    if ( !count() ) throw "Bloom filter is not set";
    auto m = filter.size();
    auto s = order.size();
    efilter.clear();
    for ( size_t i=0; i<s; i++ )
    {
        auto & c = order[i];
        std::vector<SecureMod> partial_res;
        for ( size_t j=0; j<m; j++ )
            if ( filter[j] )
            {
                partial_res.push_back( math::equal(c,j) );
                nMulsC += SZ-1;
            }
        efilter.push_back( math::add_vector(partial_res) );
    }
    // compress goes here
}

template <int SZ> void
EFilter<SZ>::sortFast(size_t logp)
{
    if ( !count() ) throw "Bloom filter is not set";
    auto s = order.size();
    auto n = SecureMod::slots();
    auto nsp = n*s*logp;
    filter.resize(nsp, 0); // make m filter divisible by n*logp

    // group filter indexes following policy
    std::vector<std::vector<unsigned long long>> fu;
    for ( size_t i=0; i<s; i++ )
    {
        std::vector<unsigned long long> poly;
        for ( size_t j=0; j<n; j++ )
        {
            unsigned long long plain = 0;
            for ( size_t k=0; k<logp; k++ )
                plain = (plain<<1) + bool( filter[i+(j*logp+k)*s] );
            poly.push_back(plain);
        }
        fu.push_back(poly);
    }

    efilter.clear();
    for ( size_t i=0; i<s; i++ )
    {
        auto & c = order[i];
        std::vector<SecureMod> partial_res;
        for ( size_t j=0; j<s; j++ )
        {
            partial_res.push_back( math::equal(c, j) * fu[j] );
            nMulsC += SZ-1;
            nMulsP++;
        }
        efilter.push_back( math::add_vector(partial_res) );
    }
}

} // bloom
