#include "Transaction.hpp"

c_Transaction::c_Transaction(t_PhysicalAddress p_phyAddr,int p_CreatedTime) {
    m_phyAddr = p_phyAddr;
    m_CreatedTime = p_CreatedTime;
}

t_PhysicalAddress c_Transaction::getMPhyAddr() const {
    return m_phyAddr;
}

int c_Transaction::getMCreatedTime() const {
    return m_CreatedTime;
}
