#ifndef NODE_HPP
#define NODE_HPP

#include "types.hpp"
#include "Packet.hpp"
#include "Transaction.hpp"


class c_Node {
    private:
        int m_NodeId;
public:
    int getMNodeId() const;

private:

    int m_Type;

    int m_LastDir;

    t_Coordinate m_Coordinate;

    t_Neighbours m_Neighbours;


public:

    queue<c_Transaction *>* m_InReq;

    queue<c_Transaction *>* m_OutResp;

    vector<queue<c_Packet *>> m_InputBuffer;

    vector<queue<c_Packet *>> m_OutputBuffer;

    c_Node(int p_NodeId,t_NodeType p_NodeType);

    void f_SetNeighbour(int p_Index,c_Node* p_Neighbour);

    t_NodeType f_GetType() const;

    void f_fetch();

    void f_decode();

    void f_issue(t_RoutingTable& p_RoutingTable);

    void f_execute();
};

#endif
