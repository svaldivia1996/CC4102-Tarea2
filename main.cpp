#include <bits/stdc++.h>
using namespace std;

void printSolution(vector<int> &dist)
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < dist.size(); i++)
        printf("%d \t\t %d\n", i, dist[i]);
}


int minDistance(vector<int> dist, vector<bool> visited)
{

    int min = INT_MAX, min_index;

    for (int v = 0; v < dist.size(); v++)
        if (visited[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

vector<int> DijskstraSlow(int n, vector<pair<int, int>> *graph, int source)
{
    vector<int> dist(n, INT_MAX);   // array distancias
    vector<bool> visited(n, false); // array visitedios
    dist[source] = 0;               // siempre la distancia a si mismo es 0

    for (int node = 0; node < n; node++)
    {
        int minIndex = minDistance(dist, visited);

        visited[minIndex] = true;
        node = minIndex;

        int v;
        int w; 
        // cout << "Node " << node << " makes an edge with \n";
        //para la recursion del sobre la lista https://www.geeksforgeeks.org/graph-implementation-using-stl-for-competitive-programming-set-2-weighted-graph/
        for (auto it = graph[node].begin(); it != graph[node].end(); it++)
        {
            v = it->first;
            w = it->second;
            if (!visited[v] and w > 0 and
                dist[minIndex] + w < dist[v])
            {
                // dist[node] = dist[minIndex] + graph[minIndex][node].second;
                dist[v] = dist[minIndex] + w;
            }
        }
    }

    printSolution(dist);
    return dist;

}

int main()
{
    int n = 5; //cant de nodos
    vector<pair<int, int>> graph[n + 1]; //inic del lista de adj
    graph[0].push_back({1, 2});
    graph[0].push_back({3, 1});
    graph[1].push_back({0, 2});
    graph[1].push_back({4, 5});
    graph[1].push_back({2, 4});
    graph[2].push_back({1, 4});
    graph[2].push_back({3, 3});
    graph[2].push_back({4, 1});
    graph[3].push_back({0, 1});
    graph[3].push_back({2, 3});
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 1});
    DijskstraSlow(n, graph, 0);
    return 0;
}