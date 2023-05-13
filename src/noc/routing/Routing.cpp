#include "Routing.hpp"
using namespace std;

const t_RoutingTable &c_Routing::f_getMRoutingTable() const {
    return m_RoutingTable;
}

c_Routing::c_Routing(t_RoutingAlgorithm p_RoutingAlgorithm, t_AdjacencyList p_Neighbours,
                     vector<t_Coordinate> p_Coordinates) {
    if (p_RoutingAlgorithm == E_ShortestPathAlgorithm) {
        m_RoutingTable = c_ShortestPathRouting::f_GetRoutingTable(p_Neighbours, p_Coordinates);
    }
}

