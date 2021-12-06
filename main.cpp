#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <omp.h>

#include "dijkstra.h"

using namespace std;

// Find the map length. 
int findN(ifstream& mapFile)
{
    // Read first line. 
    string line;
    getline(mapFile, line);

    // Find N.
    auto it = line.end() - 1;
    for (; *it != 'n'; --it) {}
    int N = stoi(string(it + 1, line.end())) + 1;

    return N;
}

// Read map file and write distance to cost. 
void readMap(ifstream& mapFile, vector<vector<int>>& cost)
{
    string line;
    int row = 0, col = 0;

    while (getline(mapFile, line))
    {
        string::size_type start = line.find(",") + 1;
        string::size_type end = start;
        col = 0;

        while (end != string::npos)
        {
            end = line.find(',', start);
            string num;

            if (end == string::npos)
            {
                #if defined(__linux__) || defined(__APPLE__)
                num = line.substr(start, line.size() - start - 1);
                #else
                num = line.substr(start, line.size() - start);
                #endif
            }
            else
            {
                num = line.substr(start, end - start);
            }

            if (num.compare("MAX") != 0)
            {
                cost[row][col] = stoi(num);
            }

            start = end + 1;
            ++col;
        }

        ++row;
    }
}

int main(int argc, char* argv[])
{
    // Read the map file. 
    ifstream mapFile("mapDist10000.csv");
    if (! mapFile.is_open())
    {
        cerr << "File open error." << endl;
        return -1;
    }

    // Find length of the map, initialize cost and read map file. 
    int N = findN(mapFile);
    vector<vector<int>> cost(N, vector<int>(N, MAX));
    readMap(mapFile, cost);

    vector<int> path;
    double start, end;

    // Execute dijkstra and measure execution time. 
    start = omp_get_wtime();
    cout << "Cost: " << dijsktra(N, cost, path, 519, 1106, 1) << endl;
    end = omp_get_wtime();

    // Print the shortest path. 
    cout << "Path: ";
    for (auto it = path.begin(); it < path.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;

    // Print the execution time. 
    cout << "Execution time: " << end - start << endl;

    return 0;
}
