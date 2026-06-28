#include "simulator.h"
#include <iostream>
#include <chrono>
#include <random>
#include <string>

vector<vector<int>> makeGrid(int rows, int cols, int seed=42){
    mt19937 rng(seed);
    uniform_int_distribution<int> dist(0,4);
    vector<vector<int>> grid(rows, vector<int>(cols, 0));
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            if(dist(rng)==4) grid[i][j]=1;
    grid[0][0]=grid[0][cols-1]=grid[rows-1][0]=grid[rows-1][cols-1]=0;
    return grid;
}

vector<AGV> makeAGVs(int n, int rows, int cols, const vector<vector<int>> &grid, int seed=99){
    mt19937 rng(seed);
    uniform_int_distribution<int> rowDist(0, rows-1);
    uniform_int_distribution<int> colDist(0, cols-1);

    set<pair<int,int>> used;
    vector<AGV> agvs;
    int id = 1;
    while((int)agvs.size() < n){
        int sx=rowDist(rng), sy=colDist(rng);
        int gx=rowDist(rng), gy=colDist(rng);
        if(grid[sx][sy]==1 || grid[gx][gy]==1) continue;
        if(used.count({sx,sy}) || used.count({gx,gy})) continue;
        if(make_pair(sx,sy)==make_pair(gx,gy)) continue;
        used.insert({sx,sy}); used.insert({gx,gy});
        agvs.push_back({id++, {sx,sy}, {gx,gy}});
    }
    return agvs;
}

int main(int argc, char* argv[]){
    int rows=20, cols=20, n_agvs=10;
    if(argc>=2) rows=cols=stoi(argv[1]);
    if(argc>=3) n_agvs=stoi(argv[2]);

    cout << "Grid: " << rows << "x" << cols
         << " | AGVs: " << n_agvs << "\n\n";

    auto grid = makeGrid(rows, cols);
    auto agvs = makeAGVs(n_agvs, rows, cols, grid);

    auto t1 = chrono::high_resolution_clock::now();
    bool success = simulate(grid, agvs);
    auto t2 = chrono::high_resolution_clock::now();

    double ms = chrono::duration<double,milli>(t2-t1).count();

    if(success){
        cout << "\nCollision-free paths found for all " << n_agvs << " AGVs\n";
        cout << "Total planning time: " << ms << " ms\n";
    } else {
        cout << "\nFailed to find collision-free paths\n";
    }
    return 0;
}