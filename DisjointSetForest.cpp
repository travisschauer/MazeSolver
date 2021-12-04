//
// Created by rwkramer on 11/20/20.
//

#include "DisjointSetForest.h"

DisjointSetForest::DisjointSetForest(uint32_t nEl) {

    rank = new uint8_t[nEl];
    elements = new uint32_t[nEl];

    for (int i=0;i<nEl;i++) {
        rank[i] = 0;
        elements[i] = i;
    }
}

DisjointSetForest::~DisjointSetForest() {

    delete[] rank;
    delete[] elements;
}

uint32_t DisjointSetForest::dsfFind(uint32_t a) {

    if (elements[a] != a)
        elements[a] = dsfFind(elements[a]);

    return elements[a];
}

void DisjointSetForest::dsfUnion(uint32_t a,uint32_t b) {

    a = dsfFind(a);
    b = dsfFind(b);

    if (a != b) {
        if (rank[a] < rank[b])
            elements[a] = b;
        else {
            if (rank[a] == rank[b])
                rank[a]++;
            elements[b] = a;
        }
    }
}
