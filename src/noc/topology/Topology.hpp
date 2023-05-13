#include "Node.hpp"

class c_Topology{
private:
    int m_NumNodes;
    vector<t_Coordinate> m_Position;
    t_ListOfNodes m_ListOfNodes;
public:
    const t_ListOfNodes &f_getMListOfNodes() const;

public:
    explicit c_Topology(int p_NumNodes, vector<t_Coordinate> p_Position, t_AdjacencyList p_AdjacencyList);

};
