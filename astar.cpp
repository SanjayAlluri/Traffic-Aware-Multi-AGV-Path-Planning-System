#include "astar.h"

int heuristic(pair<int,int> a, pair<int,int> b){
    return abs(a.first-b.first) + abs(a.second-b.second);
}

vector<pair<int,int>> astar(
    vector<vector<int>> &grid,
    vector<vector<int>> &traffic,
    ReservationTable &reservations,
    pair<int,int> start,
    pair<int,int> goal,
    int alpha
){
    int rows = grid.size();
    int cols = grid[0].size();

    using State = pair<pair<int,int>, int>;
    priority_queue<pair<int,State>, vector<pair<int,State>>, greater<>> pq;

    unordered_map<State, int, StateHash> cost;
    unordered_map<State, State, StateHash> parent;
    unordered_set<State, StateHash> visited;

    State init = {start, 0};
    pq.push({0, init});
    cost[init] = 0;

    bool found = false;
    State goal_state;

    while(!pq.empty()){
        auto f = pq.top().first;
        auto curr=pq.top().second;
        pq.pop();
        auto pos = curr.first;
        auto t=curr.second;

        if(visited.count(curr)) continue;
        visited.insert(curr);

        if(pos == goal){
            found = true;
            goal_state = curr;
            break;
        }

        vector<pair<int,int>> dirs = {{1,0},{-1,0},{0,1},{0,-1},{0,0}};
        for(auto it : dirs){
            int nx = pos.first + it.first;
            int ny = pos.second + it.second;
            int nt = t + 1;

            if(nx < 0 || ny < 0 || nx >= rows || ny >= cols) continue;
            if(grid[nx][ny] == 1) continue;

            State next = {{nx,ny}, nt};
            if(visited.count(next)) continue;
            if(reservations.count({nt, {nx,ny}})) continue;

            int new_cost = cost[curr] + 1 + alpha * traffic[nx][ny];
            if(!cost.count(next) || new_cost < cost[next]){
                cost[next] = new_cost;
                parent[next] = curr;
                int priority = new_cost + heuristic({nx,ny}, goal);
                pq.push({priority, next});
            }
        }
    }

    if(!found) return {};

    vector<pair<int,int>> path;
    State s = goal_state;
    while(parent.count(s)){
        path.push_back(s.first);
        s = parent[s];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());
    return path;
}