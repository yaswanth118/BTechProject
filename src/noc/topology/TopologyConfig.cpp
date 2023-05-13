#include "TopologyConfig.hpp"

int c_TopologyConfig::f_getMNumNodes() const {
    return m_NumNodes;
}

const vector<t_Coordinate> &c_TopologyConfig::f_getMPosition() {
    return m_Position;
}

const t_AdjacencyList &c_TopologyConfig::f_getMNeighbours() {
    return m_Neighbours;
}

void f_Swap(int &u, int &v, vector<t_Coordinate > &p_Coordinates) {
    if (get<0>(p_Coordinates[u]) != get<0>(p_Coordinates[v])) {
        if (get<0>(p_Coordinates[u]) > get<0>(p_Coordinates[v])) {
            swap(u, v);
        }
    } else if (get<1>(p_Coordinates[u]) != get<1>(p_Coordinates[v])) {
        if (get<1>(p_Coordinates[u]) > get<1>(p_Coordinates[v])) {
            swap(u, v);
        }
    } else {
        if (get<2>(p_Coordinates[u]) > get<2>(p_Coordinates[v])) {
            swap(u, v);
        }
    }
}

c_TopologyConfig::c_TopologyConfig(const std::string& filename) {
    std::ifstream in(filename);
    int n, m;
    in >> n >> m;
    vector<t_Coordinate> l_Coordinates(n);
    t_AdjacencyList l_AdjacencyList(n);
    for (int i = 0; i < n; ++i) {
        int x, y, z, p;
        in >> x >> y >> z >> p;
        t_Coordinate l_Coordinate = {x, y, z};
        l_Coordinates[p] = l_Coordinate;
    }
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        in >> u >> v >> w;
        f_Swap(u,v,l_Coordinates);
        l_AdjacencyList[u].push_back({v, w});
    }
    m_Position = l_Coordinates;
    m_Neighbours = l_AdjacencyList;
    m_NumNodes = (int)m_Position.size();
}


