//
// Created by rwkramer on 11/13/20.
//

#include "sampler.h"

Sampler::Sampler(uint32_t nElements) {

    nEl = nElements;
    values = new uint32_t[nEl];

    for (uint32_t i=0;i<nElements;i++)
        values[i] = i;

    rd = new std::random_device;
    mt = new std::mt19937((*rd)());
}

Sampler::~Sampler() {

    delete[] values;
}

uint32_t Sampler::sample() {
    uint32_t
        r,pos;
    std::uniform_int_distribution<>
        dis(0,nEl-1);

    pos = dis(*mt);
    r = values[pos];
    nEl--;
    values[pos] = values[nEl];

    return r;
}