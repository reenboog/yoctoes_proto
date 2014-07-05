#ifndef __ROAD_MAP_H_
#define __ROAD_MAP_H_

class RoadMap {
public:
    RoadMap(int size = 2);
    ~RoadMap();

    void addEdge(int u, int v);
private:
    int verticesCount_;
    int **edges_;
};


#endif //__ROAD_MAP_H_
