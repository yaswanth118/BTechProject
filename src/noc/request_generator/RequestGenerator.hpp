#include "Node.hpp"
class c_RequestGenerator {
private:
    t_ListOfNodes m_ListOfNodes;
public:
    explicit c_RequestGenerator(t_ListOfNodes p_ListOfNodes);
    void f_GenerateRandRequest(int p_ClkCycle);
    void f_GenerateRequest(int p_ClkCycle);
    void f_ReadTC();
    vector<vector<pair<int, int>>> m_Packets;
};