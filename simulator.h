#pragma once
#include "astar.h" 

struct AGV {
    int id;
    pair<int,int> start;
    pair<int,int> goal;
    vector<pair<int,int>> path;
};

bool simulate(vector<vector<int>> &grid, vector<AGV> &agvs);