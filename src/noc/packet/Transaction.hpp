#include "types.hpp"

#ifndef TRANSACTION_H
#define TRANSACTION_H
class c_Packet;

class c_Transaction {
private:
    t_PhysicalAddress m_phyAddr;
    int m_CreatedTime;
public:
    int getMCreatedTime() const;

public:
    t_PhysicalAddress getMPhyAddr() const;

public:
    c_Transaction(t_PhysicalAddress p_phyAddr,int p_CreatedTime);
};


#endif
