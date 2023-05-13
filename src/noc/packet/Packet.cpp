#include "Packet.hpp"

int c_Packet::getMSrc() const {
    return m_Src;
}

void c_Packet::setMSrc(int mSrc) {
    m_Src = mSrc;
}

int c_Packet::getMDest() const {
    return m_Dest;
}

void c_Packet::setMDest(int mDest) {
    m_Dest = mDest;
}

c_Packet::c_Packet(int p_Src, int p_Dest) {
    srand(time(0));
    m_Src = p_Src;
    m_Dest = p_Dest;
    pid = rand() % 100;

}

t_DirectionId c_Packet::getMLastDirection() const {
    return m_LastDirection;
}

void c_Packet::setMLastDirection(t_DirectionId mLastDirection) {
    m_LastDirection = mLastDirection;
}

void c_Packet::setMNextNodeType(t_NodeType mNextNodeType) {
    m_NextNodeType = mNextNodeType;
}

t_NodeType c_Packet::getMNextNodeType() const {
    return m_NextNodeType;
}

int c_Packet::getPid() const {
    return pid;
}
