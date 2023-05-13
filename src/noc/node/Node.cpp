#include "Node.hpp"

c_Node::c_Node(int p_NodeId, t_NodeType p_NodeType) {
    m_NodeId = p_NodeId;
    m_Type = p_NodeType;
    m_LastDir = E_East | E_Prev;
    m_InReq = new queue<c_Transaction *>();

    if (p_NodeType == E_Type_Switch) {
        m_Neighbours.resize(E_Switch_Size);
        m_InputBuffer.resize(E_Switch_Size);
        m_OutputBuffer.resize(E_Switch_Size);
    } else {
        m_Neighbours.resize(E_Repeater_Size);
        m_InputBuffer.resize(E_Switch_Size);
        m_OutputBuffer.resize(E_Switch_Size);
    }
}

void c_Node::f_SetNeighbour(int p_Index, c_Node *p_Neighbour) {
    m_Neighbours[p_Index] = p_Neighbour;
}

int c_Node::f_GetType() const {
    return m_Type;
}

void c_Node::f_fetch() {
    // TODO Pull the transaction into Queue.
    // Create a Network Packet.
    // Push the Network Packet into Queue.
    std::ofstream file;
    file.open("src/output/log.txt", ios::app);
    if (!file) {
        throw std::invalid_argument("Configuration file not found.");
    }
    if(m_Type == E_Type_Switch){
        if (!m_InReq->empty()) {
            c_Transaction *T = m_InReq->front();
            m_InReq->pop();
            int dest = T->getMPhyAddr() >> 6;
            auto *p = new c_Packet(getMNodeId(), dest);
            m_InputBuffer[rand() % E_Switch_Size].push(p);
            file << "Packet with id " << p->getPid() << " created at node " << getMNodeId() << endl;
        }
    }
    file.close();
}

void c_Node::f_decode() {
    // Read the elements of the Queue.
    // Populate the Network Packet and Source destination and other info.
//    std::ofstream file("src/output/log.txt");
//    if (!file) {
//        throw std::invalid_argument("Configuration file not found.");
//    }
}


t_DirectionId f_OppositeDirection(t_DirectionId p_Direction, t_NodeType p_Type) {
    if (p_Type == E_Type_Switch) {
        if (p_Direction == E_North) {
            return E_South;
        } else if (p_Direction == E_East) {
            return E_West;
        } else if (p_Direction == E_Up) {
            return E_Down;
        }
    } else {
        if (p_Direction == E_Next) {
            return E_Prev;
        } else {
            return E_Next;
        }
    }
}

void c_Node::f_issue(t_RoutingTable &p_RoutingTable) {
    // Scheduler.
    std::ofstream file;
    file.open("src/output/log.txt", ios::app);
    if (!file) {
        throw std::invalid_argument("Configuration file not found.");
    }
    int l_NumDirections = (m_Type == E_Type_Repeater ? E_Repeater_Size : E_Switch_Size);
    int l_NextDirection = 0;
    // Round Robin Algorithm scheduling.
    for (int i = 0; i < l_NumDirections; ++i) {
        l_NextDirection = (m_LastDir + i + 1) % l_NumDirections;
        if (!m_InputBuffer[l_NextDirection].empty()) {
            break;
        }
    }
    m_LastDir = l_NextDirection;
    if(m_Type == E_Type_Switch) {
        if (!m_InputBuffer[l_NextDirection].empty()) {
            c_Packet *l_Packet = m_InputBuffer[l_NextDirection].front();
            m_InputBuffer[l_NextDirection].pop();
            if (l_Packet->getMDest() == getMNodeId()) {
                cout << "Packet reached destination\n";
                file << "Packet with id " << l_Packet->getPid() << " reached the Destination\n";
                return;
            }
            t_DirectionId l_Direction = p_RoutingTable[getMNodeId()][l_Packet->getMDest()];
            l_Packet->setMLastDirection(l_Direction);
            c_Node *l_NextDestination = (this->m_Neighbours[l_Direction]);
            l_Packet->setMNextNodeType(l_NextDestination->f_GetType());
            m_OutputBuffer[l_Direction].push(l_Packet);
            file << "Packet with id " << l_Packet->getPid() << " is in output buffer of node " << getMNodeId()
                 << " and in direction id " << l_Direction << endl;
        }
    } else {
        if (!m_InputBuffer[l_NextDirection].empty()) {
            c_Packet *l_Packet = m_InputBuffer[l_NextDirection].front();
            m_InputBuffer[l_NextDirection].pop();
            t_DirectionId l_Direction = (l_NextDirection == E_Prev ? E_Next : E_Prev);
            c_Node *l_NextDestination = (this->m_Neighbours[l_Direction]);
            l_Packet->setMNextNodeType(l_NextDestination->f_GetType());
            m_OutputBuffer[l_Direction].push(l_Packet);
            file << "Packet with id " << l_Packet->getPid() << " is in output buffer of node " << getMNodeId()
                 << " and in direction id " << l_Direction << endl;
        }
    }
    file.close();
}


void c_Node::f_execute() {
    // Send the packet.
    std::ofstream file;
    file.open("src/output/log.txt", ios::app);
    if (!file) {
        throw std::invalid_argument("Configuration file not found.");
    }
    int l_NumDirections = (m_Type == E_Type_Repeater ? E_Repeater_Size : E_Switch_Size);
    for (int i = 0; i < l_NumDirections; ++i) {
        if (!m_OutputBuffer[i].empty()) {
            c_Packet *temp = m_OutputBuffer[i].front();
            m_OutputBuffer[i].pop();
            if (temp->getMNextNodeType() == E_Type_Switch) {
                m_Neighbours[i]->m_InputBuffer[f_OppositeDirection(temp->getMLastDirection(), E_Type_Switch)].push(
                        temp);
                file << "Packet with id " << temp->getPid() << " is in input buffer of node "
                     << m_Neighbours[i]->getMNodeId() << " and in direction id "
                     << f_OppositeDirection(temp->getMLastDirection(), E_Type_Switch) << endl;
            } else {
                if (temp->getMLastDirection() == E_East || temp->getMLastDirection() == E_North ||
                    temp->getMLastDirection() == E_Up) {
                    m_Neighbours[i]->m_InputBuffer[E_Prev].push(temp);
                    file << "Packet with id " << temp->getPid() << " is in input buffer of node "
                         << m_Neighbours[i]->getMNodeId()
                         << " and in direction id " << E_Prev << endl;
                } else {
                    m_Neighbours[i]->m_InputBuffer[E_Next].push(temp);
                    file << "Packet with id " << temp->getPid() << " is in input buffer of node "
                         << m_Neighbours[i]->getMNodeId()
                         << " and in direction id " << E_Next << endl;
                }
            }
        }
    }
    file.close();
}

int c_Node::getMNodeId() const {
    return m_NodeId;
}
