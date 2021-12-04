//
// Created by rwkramer on 11/13/20.
//

#ifndef PROJECT4_SAMPLER_H
#define PROJECT4_SAMPLER_H

#include <cstdint>
#include <random>

class Sampler {
public:
    explicit Sampler(uint32_t nElements);
    ~Sampler();

    uint32_t sample();

private:
    uint32_t
        nEl,
        *values;
    std::random_device
        *rd;
    std::mt19937
        *mt;
};


#endif //PROJECT4_SAMPLER_H
