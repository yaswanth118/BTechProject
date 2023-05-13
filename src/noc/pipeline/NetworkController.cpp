#include "NetworkController.hpp"

void c_NetworkController::f_clockCycle() {
// TODO change order when executing.
    for (auto &m_ListOfNode: m_ListOfNodes) {
        for (int i = 0; i < (m_ListOfNode->f_GetType() == E_Type_Switch ? E_Switch_Size : E_Repeater_Size); ++i) {
            if (!m_ListOfNode->m_InputBuffer[i].empty()) {
                cout << "In Input buffer of " << m_ListOfNode->getMNodeId() << " and the direction is " << i << endl;
            }
            if (!m_ListOfNode->m_OutputBuffer[i].empty()) {
                cout << "In Output buffer of " << m_ListOfNode->getMNodeId() << " and the direction is " << i << endl;
            }
        }
    }
    f_execute();
    f_issue(m_RoutingTable);
    f_decode();
    f_fetch();
}


int c_NetworkController::f_GetDirection(t_NodeId p_Src, t_NodeId p_Dest) {
    return m_RoutingTable[p_Src][p_Dest];
}

c_NetworkController::c_NetworkController(t_RoutingTable p_RoutingTable, t_ListOfNodes p_ListOfNodes) {
    m_RoutingTable = p_RoutingTable;
    m_ListOfNodes = p_ListOfNodes;

}

void c_NetworkController::f_execute() {
    for (auto & m_ListOfNode : m_ListOfNodes) {
        m_ListOfNode->f_execute();
    }
}

void c_NetworkController::f_issue(t_RoutingTable& p_RoutingTable) {
    for (auto & m_ListOfNode : m_ListOfNodes) {
        m_ListOfNode->f_issue(p_RoutingTable);
    }
}

void c_NetworkController::f_decode() {
    for (auto & m_ListOfNode : m_ListOfNodes) {
        m_ListOfNode->f_decode();
    }
}

void c_NetworkController::f_fetch() {
    for (auto & m_ListOfNode : m_ListOfNodes) {
        m_ListOfNode->f_fetch();
    }
}