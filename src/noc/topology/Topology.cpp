#include "Topology.hpp"

t_AxisType f_GetAxis(vector<t_Coordinate> &p_Position, int &i, int &j) {
    if (get<0>(p_Position[i]) != get<0>(p_Position[j])) {
        return E_XAxis;
    } else if (get<1>(p_Position[i]) != get<1>(p_Position[j])) {
        return E_YAxis;
    } else {
        return E_ZAxis;
    }
}

c_Topology::c_Topology(int p_NumNodes, vector<t_Coordinate> p_Position, t_AdjacencyList p_AdjacencyList) {
    m_NumNodes = p_NumNodes;
    m_Position = p_Position;

    vector<c_Node *> l_Address(m_NumNodes);
    for (int i = 0; i < m_NumNodes; ++i) {
        c_Node *o_Switch = new c_Node(i, E_Type_Switch);
        m_ListOfNodes.push_back(o_Switch);
        l_Address[i] = o_Switch;
    }

    t_AdjacencyList l_AdjacencyList = p_AdjacencyList;

    int l_RepeaterCounter = p_NumNodes;
    for (int i = 0; i < l_AdjacencyList.size(); ++i) {
        for (int j = 0; j < l_AdjacencyList[i].size(); ++j) {
            int l_SrcSwitch = i;
            int l_DestSwitch = l_AdjacencyList[i][j].first;
            int l_NumRepeaters = l_AdjacencyList[i][j].second;
            int l_Axis = f_GetAxis(p_Position, l_SrcSwitch, l_DestSwitch);
            c_Node *o_PrevNode = l_Address[l_SrcSwitch];
            for (int k = 0; k < l_NumRepeaters; ++k) {
                c_Node *o_Repeater = new c_Node(l_RepeaterCounter++, E_Type_Repeater);
                m_ListOfNodes.push_back(o_Repeater);
                o_Repeater->f_SetNeighbour(E_Prev, o_PrevNode);
                if (o_PrevNode->f_GetType() == E_Type_Switch) {
                    o_PrevNode->f_SetNeighbour(l_Axis * 2, o_Repeater);
                } else {
                    o_PrevNode->f_SetNeighbour(E_Next, o_Repeater);
                }
                o_PrevNode = o_Repeater;
            }
            if (o_PrevNode->f_GetType() == E_Type_Switch) {
                o_PrevNode->f_SetNeighbour(l_Axis * 2, l_Address[l_DestSwitch]);
            } else {
                o_PrevNode->f_SetNeighbour(E_Next, l_Address[l_DestSwitch]);
            }
            l_Address[l_DestSwitch]->f_SetNeighbour(l_Axis * 2 + 1, o_PrevNode);
        }
    }

}

const t_ListOfNodes &c_Topology::f_getMListOfNodes() const {
    return m_ListOfNodes;
}


