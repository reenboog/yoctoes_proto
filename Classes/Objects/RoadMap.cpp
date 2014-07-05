#include "RoadMap.h"

RoadMap::RoadMap(int size) {
    int i, j;
    if (size < 2) {
        verticesCount_ = 2;
    } else {
        verticesCount_ = size;
    }

    edges_ = new int *[verticesCount_];
    for (i = 0; i < verticesCount_; ++i) {
        edges_[i] = new int[verticesCount_];
    }
    for (i = 0; i < verticesCount_; ++i) {
        for (j = 0; j < verticesCount_; ++j) {
            edges_[i][j] = 0;
        }
    }
}

RoadMap::~RoadMap() {
    for (int i = 0; i < verticesCount_; ++i)
        delete[] edges_[i];
    delete[] edges_;
}

void RoadMap::addEdge(int u, int v) {
    //
}
