#include "ShortestPathRouting.hpp"

// TODO test if everything is going correct or not. @riteesh

t_DirectionId f_GetDirections(t_Coordinate p_FirstNode, t_Coordinate p_SecondNode){
    if (get<0>(p_FirstNode) != get<0>(p_SecondNode)) {
        return (get<0>(p_FirstNode) > get<0>(p_SecondNode))?E_West:E_East;
    } else if (get<1>(p_FirstNode) != get<1>(p_SecondNode)) {
        return (get<1>(p_FirstNode) > get<1>(p_SecondNode))?E_South:E_North;
    } else {
        return (get<2>(p_FirstNode) > get<2>(p_SecondNode))?E_Down:E_Up;
    }
}

double f_Distance(t_Coordinate i, t_Coordinate j) {
    return sqrt((get<0>(i) - get<0>(j)) * (get<0>(i) - get<0>(j))
                + (get<1>(i) - get<1>(j)) * (get<1>(i) - get<1>(j))
                + (get<2>(i) - get<2>(j)) * (get<2>(i) - get<2>(j)));
}

t_RoutingTable c_ShortestPathRouting::f_GetRoutingTable(t_AdjacencyList p_AdjacencyList,
                                                                       vector<t_Coordinate> p_CoordinatePositions) {
    int n = (int) p_AdjacencyList.size();
    vector<vector<double>> l_ShortestDistance(n, vector<double>(n, INF));
    t_RoutingTable l_ShortestNeighbour(n, vector<t_DirectionId>(n, E_NotDefined));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < p_AdjacencyList[i].size(); ++j) {
            l_ShortestDistance[i][p_AdjacencyList[i][j].first] = f_Distance(p_CoordinatePositions[i],
                                                                            p_CoordinatePositions[p_AdjacencyList[i][j].first]);
            l_ShortestNeighbour[i][p_AdjacencyList[i][j].first] = f_GetDirections(
                    p_CoordinatePositions[i], p_CoordinatePositions[p_AdjacencyList[i][j].first]);

            l_ShortestDistance[p_AdjacencyList[i][j].first][i] = f_Distance(p_CoordinatePositions[i],
                                                                            p_CoordinatePositions[p_AdjacencyList[i][j].first]);;
            l_ShortestNeighbour[p_AdjacencyList[i][j].first][i] = f_GetDirections(
                    p_CoordinatePositions[p_AdjacencyList[i][j].first], p_CoordinatePositions[i]);

        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (l_ShortestDistance[i][j] > l_ShortestDistance[i][k] + l_ShortestDistance[k][j]) {
                    l_ShortestDistance[i][j] = l_ShortestDistance[i][k] + l_ShortestDistance[k][j];
                    l_ShortestNeighbour[i][j] = l_ShortestNeighbour[i][k];
                }

            }
        }
    }
    return l_ShortestNeighbour;
}
