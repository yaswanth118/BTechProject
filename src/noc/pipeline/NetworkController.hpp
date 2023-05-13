#include "Node.hpp"


// This Contains the copy of Routing Table and List of nodes.
class c_NetworkController {
    private:
        t_RoutingTable m_RoutingTable;

        t_ListOfNodes m_ListOfNodes;

        void f_execute();

        void f_issue(t_RoutingTable& p_RoutingTable);

        void f_decode();

        void f_fetch();
    public:
        void f_clockCycle();

        int f_GetDirection(t_NodeId p_Src,t_NodeId p_Dest);

        c_NetworkController(t_RoutingTable p_RoutingTable,t_ListOfNodes p_ListOfNodes);

};