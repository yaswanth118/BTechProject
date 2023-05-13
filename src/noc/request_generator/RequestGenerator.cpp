#include "RequestGenerator.hpp"

#include <utility>



c_RequestGenerator::c_RequestGenerator(vector<c_Node *> p_ListOfNodes) {
    m_ListOfNodes = std::move(p_ListOfNodes);
}

void c_RequestGenerator::f_GenerateRandRequest(int p_ClkCycle) {

    srand(time(0));
    for (auto &m_ListOfNode: m_ListOfNodes) {
        if (m_ListOfNode->f_GetType() == E_Type_Switch) {
            if (rand() % 20 == 0) {
                int dest = rand() % m_ListOfNodes.size();
                t_PhysicalAddress destAddr = ((t_PhysicalAddress) dest) << 6;
                c_Transaction *T = new c_Transaction(destAddr, p_ClkCycle);
                m_ListOfNode->m_InReq->push(T);
            }
        }
    }
}

int AddresstoNodeId(string n)
{
    string num = n;
    int dec_value = 0;

    // Initializing base value to 1, i.e 2^0
    int base = 1;

    int len = num.length();
    for (int i = len - 7; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}
void c_RequestGenerator::f_ReadTC() {
    std::ifstream file("src/output/testcase.txt");
    if (!file) {
        throw std::invalid_argument("Configuration file not found.");
    }
    m_Packets.resize(10000);
    while (true) {
        int n, m;
        file >> n >> m;
        if (n == -1 && m == -1) {
            break;
        }
        for (int i = 0; i < m; ++i) {
            string x, y;
            file >> x >> y;
            int src = AddresstoNodeId(x);
            int dest = AddresstoNodeId(y);
            if (src > 16) {
                cout << src << endl;
            }
            m_Packets[n].push_back({src, dest});
        }
    }
}

void c_RequestGenerator::f_GenerateRequest(int p_ClkCycle) {
    if (p_ClkCycle >= 9999) {
        return;
    }
    for (int i = 0; i < m_Packets[p_ClkCycle].size(); ++i) {
        int src = m_Packets[p_ClkCycle][i].first;
        int dest = m_Packets[p_ClkCycle][i].second;
        t_PhysicalAddress destAddr = ((t_PhysicalAddress) dest) << 6;
        c_Transaction *T = new c_Transaction(destAddr, p_ClkCycle);
        m_ListOfNodes[src]->m_InReq->push(T);
    }

}
