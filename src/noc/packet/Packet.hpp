#ifndef PACKET_HPP
#define PACKET_HPP
#include "types.hpp"

class c_Packet {
public:
    int getMSrc() const;

    int getPid() const;

    void setMSrc(int mSrc);

    int getMDest() const;

    void setMDest(int mDest);

    c_Packet(int p_Src, int p_Dest);

    void setMNextNodeType(t_NodeType mNextNodeType);

    int m_CreatedTime;
private:
    int pid;
    int m_Src;
    int m_Dest;
    t_DirectionId m_LastDirection;
    t_NodeType m_NextNodeType;
public:
    t_NodeType getMNextNodeType() const;

public:
    t_DirectionId getMLastDirection() const;

    void setMLastDirection(t_DirectionId mLastDirection);

};

#endif