#include "ConfigReader.hpp"
// No need of TopologyConfig.hpp as it's already included in Routing
#include "Routing.hpp"
#include "TestCaseGenerator.hpp"
#include "Topology.hpp"
#include "NetworkController.hpp"
#include "RequestGenerator.hpp"
class c_NetworkController;

#define MAX_CLK_CYCLES 25

class c_Node;

void f_InitializeSimulation(t_RoutingTable p_RoutingTable, t_ListOfNodes p_ListOfNodes) {
    c_NetworkController *o_NetworkController = new c_NetworkController(p_RoutingTable, p_ListOfNodes);
    c_RequestGenerator* o_RequestGenerator = new c_RequestGenerator(p_ListOfNodes);
    int co = 0;
    o_RequestGenerator->f_ReadTC();

    for (int i = 0; i < MAX_CLK_CYCLES; ++i) {
        cout << "cycle number " << i << endl;
//                std::ofstream file;
//        file.open("src/output/log.txt", ios::app);
//        file << "cycle number " << i << endl;
//        file.close();
//        o_RequestGenerator->f_GenerateRandRequest(i);
//        o_RequestGenerator->f_GenerateRequest(i);
        if (i == 0) {
            int dest = 7;
            t_PhysicalAddress destAddr = ((t_PhysicalAddress) dest) << 6;
            c_Transaction *T = new c_Transaction(destAddr,i);
            p_ListOfNodes[6]->m_InReq->push(T);
        }
        o_NetworkController->f_clockCycle();
    }
}

int main() {
    ConfigReader reader("src/input/sim.cfg");
    int src[] = {1};
    c_TestCase * TC = new c_TestCase();
    TC->tc_generator(1,  src);
    string filename = reader.GetString("Hierarchy", "TopologyStruct");
    c_TopologyConfig *o_TopologyConfig = new c_TopologyConfig(filename);

    c_Routing *o_Routing = new c_Routing(E_ShortestPathAlgorithm, o_TopologyConfig->f_getMNeighbours(),
                                         o_TopologyConfig->f_getMPosition());


    int l_Layers = reader.GetInteger("Setting", "Layers");
    vector<c_Topology *> o_TopologyLayers;
    for (int i = 0; i < l_Layers; ++i) {
        c_Topology *o_Topology = new c_Topology(o_TopologyConfig->f_getMNumNodes(), o_TopologyConfig->f_getMPosition(),
                                                o_TopologyConfig->f_getMNeighbours());
        o_TopologyLayers.push_back(o_Topology);
    }


//    auto l_RoutingTable = o_Routing->f_getMRoutingTable();
//    for (int i = 0; i < l_RoutingTable.size(); ++i) {
//        for (int j = 0; j < l_RoutingTable[i].size(); ++j) {
//            cout << i << " " << j << " Directions is " << l_RoutingTable[i][j] << endl;
//        }
//        cout << endl;
//    }



    f_InitializeSimulation(o_Routing->f_getMRoutingTable(),o_TopologyLayers[0]->f_getMListOfNodes());

    cout << "Execution Completed\n";

    return 0;
}
