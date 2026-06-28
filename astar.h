#pragma once
#include <bits/stdc++.h>
using namespace std;

struct PairHash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 16);
    }
};

struct StateHash {
    size_t operator()(const pair<pair<int,int>,int>& s) const {
        size_t h1 = PairHash()(s.first);
        return h1 ^ (hash<int>()(s.second) << 32);
    }
};

struct ReservationHash {
    size_t operator()(const pair<int,pair<int,int>>& r) const {
        return hash<int>()(r.first) ^ (PairHash()(r.second) << 16);
    }
};

using ReservationTable = unordered_map<pair<int,pair<int,int>>, int, ReservationHash>;

vector<pair<int,int>> astar(
    vector<vector<int>> &grid,
    vector<vector<int>> &traffic,
    ReservationTable &reservations,
    pair<int,int> start,
    pair<int,int> goal,
    int alpha
);