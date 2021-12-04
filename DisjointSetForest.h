//
// Created by rwkramer on 11/20/20.
//

#ifndef PROJECT4_DISJOINTSETFOREST_H
#define PROJECT4_DISJOINTSETFOREST_H


#include <stdint-gcc.h>

class DisjointSetForest {
public:
    DisjointSetForest(uint32_t nEl);
    ~DisjointSetForest();

    uint32_t
        dsfFind(uint32_t a);
    void
        dsfUnion(uint32_t a,uint32_t b);
private:
    uint8_t
        *rank;
    uint32_t
        *elements;
};


#endif //PROJECT4_DISJOINTSETFOREST_H
