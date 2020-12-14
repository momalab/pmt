#pragma once

#include <iostream>
#include <functional>
#include <string>

namespace bloom
{

class Hash
{
    private:
        std::hash<std::string> strhash;
        size_t seed;
        size_t mod;

    public:
        Hash(){}
        Hash(size_t seed, size_t mod)
        { this->seed = seed; this->mod = mod; }
        Hash(const Hash & hash) : Hash(hash.seed, hash.mod) {}

        size_t getModulus() const { return mod; }
        size_t hash(const std::string & str) const
        { return ( strhash(str) ^ seed ) % mod; }

        friend std::ostream & operator<<(std::ostream & os, const Hash & hash);
};

} // bloom
