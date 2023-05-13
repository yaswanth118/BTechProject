#ifndef INC_3D_NETWORK_ON_CHIP_TYPES_H
#define INC_3D_NETWORK_ON_CHIP_TYPES_H

#include <bits/stdc++.h>

using namespace std;

enum t_DirectionId{
    E_Type_Switch = 0,
    E_Type_Repeater = 1,

    E_Prev = 0,
    E_Next = 1,

    E_NotDefined = -1,
    E_East=0,
    E_West=1,
    E_North = 2,
    E_South = 3,
    E_Up = 4,
    E_Down = 5,

    E_Repeater_Size = 2,
    E_Switch_Size = 6
};

enum t_AxisType{
    E_XAxis = 0,
    E_YAxis =1,
    E_ZAxis = 2
};


#define t_Neighbours vector<c_Node*>
#define t_ListOfNodes vector<c_Node*>
typedef int t_Axis;
typedef std::tuple<int,int,int> t_Coordinate;
typedef int t_NodeId;
typedef std::vector<vector<pair<int,int>>> t_AdjacencyList;
typedef unsigned long long t_PhysicalAddress;

typedef std::string t_FileName;
typedef std::tuple<int,int,int> t_RepeaterId;
typedef int t_NodeType;
typedef vector<vector<t_DirectionId>> t_RoutingTable;

enum t_RoutingAlgorithm{
    E_ShortestPathAlgorithm = 1

};

#endif //INC_3D_NETWORK_ON_CHIP_TYPES_H
