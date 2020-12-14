#pragma once

#include <string>
#include <vector>
#include <utility>

#include "hash.hpp"

namespace bloom
{

class Filter
{
    protected:
        std::vector<Hash> hashes;
        std::vector<size_t> filter;

    public:
        Filter() {}
        Filter(size_t m, size_t h);
        Filter(const std::vector<Hash> & hashes,
            const std::vector<size_t> & filter = std::vector<size_t>() );
        Filter(const std::vector<std::vector<size_t>> params,
            const std::vector<size_t> & filter = std::vector<size_t>() );

        bool contains(const std::string & data);
        bool contains(const std::vector<size_t> & indices);
        size_t count();
        std::vector<size_t> hash(const std::string & data);
        std::vector< std::pair<size_t,size_t> > insert(const std::string & data);
        std::vector<std::vector< std::pair<size_t,size_t> >> insert(
            const std::vector<std::string> & database);
        std::vector< std::pair<size_t,size_t> > insert(
            const std::vector<size_t> & indices);
        std::vector<size_t> query(const std::string & data);
        std::vector<size_t> query(const std::vector<size_t> & indices);
        std::vector< std::pair<size_t,size_t> > remove(const std::string & data);
        std::vector< std::pair<size_t,size_t> > remove(
            const std::vector<size_t> & indices);
        bool save(const std::string & configname, const std::string & filtername);
        bool saveConfig(const std::string & configname);
        bool saveFilter(const std::string & filtername);
        size_t size();
        void sort(const std::vector<size_t> & order);
};

} // bloom
