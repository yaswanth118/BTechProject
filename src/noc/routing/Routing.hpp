#include "types.hpp"
#include "TopologyConfig.hpp"
#include "ShortestPathRouting.hpp"

using namespace std;

class c_Routing {
private:
    t_RoutingTable m_RoutingTable;

public:
    const t_RoutingTable &f_getMRoutingTable() const;

    c_Routing(t_RoutingAlgorithm p_RoutingAlgorithm, t_AdjacencyList p_Neighbours, vector<t_Coordinate> p_Coordinates);

};
