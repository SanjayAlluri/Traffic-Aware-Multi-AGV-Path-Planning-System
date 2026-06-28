#include "simulator.h"
#include <iostream>

bool simulate(vector<vector<int>> &grid, vector<AGV> &agvs){
    int rows = grid.size(), cols = grid[0].size();
    vector<vector<int>> traffic(rows, vector<int>(cols, 0));
    ReservationTable reservations;

    for(auto &agv : agvs){
        ReservationTable empty;
        vector<vector<int>> zero_traffic(rows, vector<int>(cols, 0));
        auto optimal = astar(grid, zero_traffic, empty, agv.start, agv.goal, 0);
        int optimal_len = optimal.empty() ? -1 : (int)optimal.size() - 1;

        auto path = astar(grid, traffic, reservations, agv.start, agv.goal, 2);
        if(path.empty()){
            cout << "NOT POSSIBLE for AGV " << agv.id << "\n";
            return false;
        }
        agv.path = path;
        int actual_len = (int)path.size() - 1;

        cout << "AGV " << agv.id
             << " | path_len=" << actual_len
             << " | optimal=" << optimal_len
             << " | overhead=" << (optimal_len > 0 ? (actual_len - optimal_len) : 0)
             << " extra steps\n";

        for(int t = 0; t < (int)path.size(); t++){
            reservations[{t, path[t]}] = 1;
            traffic[path[t].first][path[t].second]++;
        }
    }
    return true;
}