#ifndef BLOOM_H
#define BLOOM_H

#include <vector>
#include <cmath>
#include <iostream>
#include <tuple>

extern bool IsDebugOutput;

#define MY_DEBUG_ONLY(x) { if(IsDebugOutput) {x}  }

template <typename T>
class Bloom
{
private:
    size_t N;
    size_t m;
    size_t k;
    double p;
    std::vector<bool> bits;

    auto CalcTwoHashes(const T &_item)
    {
        auto h1 = std::hash<T>{}(_item);
//        auto h2 = std::hash<decltype(h1)>{}(~h1>>1);  // vs. ~h1  vs. ~h1<<1
        auto h2 = std::hash<decltype(h1)>{}(~h1<<4);  // vs. ~h1  vs. ~h1<<1
        return std::make_tuple(h1, h2);
    }

public:
    Bloom() = delete;
    Bloom(size_t _N, double _p = 0.01) : N(_N), p(_p)
    {
        //MY_DEBUG_ONLY( std::cout << "N = " << N << std::endl; )
        //MY_DEBUG_ONLY( std::cout << "p = " << p << " (" << p*100 << "%)" << std::endl; )

        m = -(N*log2(p))/log(2); // vs. - N*log2(p)/log(2)
        //MY_DEBUG_ONLY( std::cout << "m = " << m << " (bits)" << std::endl; )

        k = round(m*log(2)/N);
        //MY_DEBUG_ONLY( std::cout << "k = " << k << std::endl; )

        MY_DEBUG_ONLY( std::cout << N << "\t" << m << "\t" << k << "\t"; )

        bits.resize(m);
    };

    void Add(const T &_item)
    {
        auto [h1, h2] = CalcTwoHashes(_item);
        for (size_t i = 0; i < k; ++i)
        {
            size_t ind = (h1 + i*h2)%(m);
            bits[ind] = true;
        }
    }

    bool Contains(const T &_item)
    {
        auto [h1, h2] = CalcTwoHashes(_item);
        for (size_t i = 0; i < k; ++i)
        {
            size_t ind = (h1 + i*h2)%(m);
            if (!bits[ind])
                return false;
        }
        return true;
    }
};

#endif // BLOOM_H
