#pragma once 

#include <type_traits>
#include <boost/random.hpp>

namespace base {

extern boost::mt19937 rnd;

template<typename T>
T Rand(T min, T max) {
    if(std::is_same<T, int>::value) {
        boost::uniform_int<> rndint(min, max);
        return rndint(rnd);
    } else if (std::is_same<T, double>::value) {
        boost::uniform_real<> rndfloat64(min, max);
        return rndfloat64(rnd);
    } else {
        return min;
    }
}

}