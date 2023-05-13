#include "types.hpp"

class c_TopologyConfig {
    private:
        int m_NumNodes;

        vector<t_Coordinate> m_Position;

        t_AdjacencyList m_Neighbours;

    public:
        int f_getMNumNodes() const;

        const vector<t_Coordinate> & f_getMPosition();

        const t_AdjacencyList &f_getMNeighbours();

        c_TopologyConfig(const std::string& filename);
};