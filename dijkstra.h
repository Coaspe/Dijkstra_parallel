#pragma once

#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

constexpr int MAX = 99999999;

int dijsktra(const int N, const vector<vector<int>>& cost, vector<int>& path, const int source, const int target, const int numThreads);