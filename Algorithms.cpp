//ID:207988213
//E-mail: haleviadiel@gmail.com
#include <sstream>
#include <vector>
#include <iostream>
#include <climits>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include "Graph.hpp"
#include "Algorithms.hpp"
#include <string>
#include <stack>

using namespace std;

namespace ariel
{


std::string Algorithms::isConnected(const Graph g)
 {

    std::vector<bool> visited(g.get_matrix().size(), false);

        if(g.get_matrix().size()==0||g.get_matrix().size()==1)
                return "1";
      for (int ver=0;ver<g.get_matrix().size();ver++)
        {
            // Start DFS all on the  vertices

            dfs(g.get_matrix(), visited, ver);

            // Check if all vertices are visited
            for (bool v : visited) {
                if (!v) {
                    return "0";  // If any vertex is not visited, the graph is not connected
                }
        }
        }

        return "1";  // All vertices were visited
    

}

std::string Algorithms::shortestPath(const Graph& graph, int source, int destination) {
     
        
         if (hasNegativeWeights(graph.get_matrix())) {
                return bellmanFord(graph.get_matrix(), source, destination);
         }
        if (isUnweighted(graph.get_matrix())) {
            // Unweighted graph using adjacency matrix
            return bfsShortestPath(graph.get_matrix(), source, destination);
        } else if(!isUnweighted(graph.get_matrix()) ){
            // Weighted graph using adjacency list
            return dijkstra(graph.get_matrix(), source, destination);
        } 
     return "";
        
}
 bool Algorithms::isUnweighted(const std::vector<std::vector<int>> &matrix) {
        for (const auto &row : matrix) {
            for (int weight : row) {
                if (weight != 0 && weight != 1) {
                    return false;
                }
            }
        }
        return true;
    }
bool Algorithms::hasNegativeWeights(const std::vector<std::vector<int>> &matrix) {
        for (const auto &row : matrix) {
            for (int weight : row) {
                if (weight < 0) {
                    return true;
                }
            }
        }
        return false;
    }
    std::string Algorithms::isContainsCycle( const Graph g) 
    {
        if(negativeCycle(g)!="No negative cycle found.")
        {
            return "0";
        }
    stringstream str;
    int numNodes = g.get_matrix().size();
    std::vector<bool> visited(numNodes, false);
    std::vector<int> path;
    std::string cycle;

    for (int node = 0; node < numNodes; ++node) {
        if (!visited[node]) {
            if (hasCycleDFS(g.get_matrix(), visited, path, node, -1, cycle)) {
                str << "The cycle is: " << cycle ;
                return str.str();
            }
        }
    }

    return "0";
}
bool Algorithms::hasCycleDFS(const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& path, int node, int parent, string &cycle)   {
            visited[node] = true;
    path.push_back(node);

    for (int neighbor = 0; neighbor < graph.size(); ++neighbor) {
        if (graph[node][neighbor]) {
            if (!visited[neighbor]) {
                if (hasCycleDFS(graph, visited, path, neighbor, node, cycle)) {
                    return true;
                }
            } else if (neighbor != parent) {
                // Cycle found, extract the cycle path
                ostringstream oss;
                auto it = find(path.begin(), path.end(), neighbor);
                for (auto i = it; i != path.end(); ++i) {
                    oss << *i << "->";
                }
                oss << neighbor;
                cycle = oss.str();
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}
std::string Algorithms::negativeCycle(const Graph& g)
{
    // Get the number of vertices in the graph
    int numVertices = g.get_matrix().size();

    // Get the adjacency matrix of the graph
    const auto& matrix = g.get_matrix();

    // Initialize distance array to store shortest distances from source vertex
    std::vector<int> distance(numVertices, INT_MAX);
    distance[0] = 0; // Assuming source vertex is 0

    // Relax edges repeatedly
    for (int i = 0; i < numVertices - 1; ++i)
    {
        for (int u = 0; u < numVertices; ++u)
        {
            for (int v = 0; v < numVertices; ++v)
            {
                if (matrix[u][v] != 0)
                {
                    if (distance[u] != INT_MAX && distance[u] + matrix[u][v] < distance[v])
                    {
                        distance[v] = distance[u] + matrix[u][v];
                    }
                }
            }
        }
    }

    // Check for negative cycles
    for (int u = 0; u < numVertices; ++u)
    {
        for (int v = 0; v < numVertices; ++v)
        {
            if (matrix[u][v] != 0)
            {
                if (distance[u] != INT_MAX && distance[u] + matrix[u][v] < distance[v])
                {
                    // Found a negative cycle
                    return "Negative cycle found.";
                }
            }
        }
    }

    // No negative cycle found
    return "No negative cycle found.";
}





// Depth-First Search (DFS) function for traversing a graph
    void Algorithms::dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, int start) 

    {
        
        visited[start] = true;

        for (int i = 0; i < matrix[start].size(); ++i) {
            if (matrix[start][i] != 0 && !visited[i]) {
                dfs(matrix, visited, i);
            }
        }
    }
    

   



 

 

string Algorithms::isBipartite(Graph g) 
{
    int size = g.get_matrix().size();
    std::vector<int> color(size, 0); // 0: not colored, 1: color 1, -1: color 2
    std::queue<int> q;

    for (int i = 0; i < size; ++i) {
        if (color[i] != 0) continue; // Already colored/visited
        q.push(i);
        color[i] = 1;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (int dest = 0; dest < size; ++dest) {
                if (g.get_matrix()[curr][dest] != 0) {
                    if (color[dest] == 0) { // Not colored yet
                        color[dest] = -color[curr]; // Assign opposite color
                        q.push(dest);
                    } else if (color[dest] == color[curr]) { // Conflict
                        return "0"; // Graph is not bipartite
                    }
                }
            }
        }
    }

    std::vector<int> group1, group2;

    for (int i = 0; i < size; ++i) {
        if (color[i] == 1) {
            group1.push_back(i);
        } else {
            group2.push_back(i);
        }
    }

    std::stringstream result;
    result << "The graph is bipartite: A={";
    for (int i = 0; i < group1.size() - 1; ++i) {
        result << group1[i] << ", ";
    }
    if (!group1.empty()) {
        result << group1.back();
    }
    result << "}, B={";
    for (int j = 0; j < group2.size() - 1; ++j) {
        result << group2[j] << ", ";
    }
    if (!group2.empty()) {
        result << group2.back();
    }
    result << "}";
    
    group1.clear();
    group2.clear();

    return result.str(); // Graph is bipartite
}




 std::string Algorithms::bfsShortestPath(const std::vector<std::vector<int>> &matrix, int start, int target) {
        int n = matrix.size();
        std::vector<bool> visited(n, false);
        std::vector<int> distance(n, INT_MAX);
        std::vector<int> parent(n, -1);

        std::queue<int> q;
        visited[start] = true;
        distance[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int i = 0; i < n; ++i) {
                if (matrix[node][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    distance[i] = distance[node] + 1;
                    parent[i] = node;
                    q.push(i);

                    if (i == target) { // Early exit if target is found
                        return constructPath(parent, start, target);
                    }
                }
            }
        }

        return "-1"; // Return an empty path if no path is found
    }
     std::string Algorithms::dijkstra(const std::vector<std::vector<int>> &matrix, int start, int target) {
        int n = matrix.size();
    std::vector<int> dist(n, INT_MAX);
    std::vector<int> parent(n, -1);
    dist[start] = 0;

    using pii = std::pair<int, int>; // {distance, node}
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (int v = 0; v < n; ++v) {
            if (matrix[u][v] != 0) { // If there is an edge
                int weight = matrix[u][v];
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // Check if there's no shortest path to the target
    if (dist[target] == INT_MAX) {
        return "-1";
    }

    return constructPath(parent, start, target);
    }
    std::string Algorithms::bellmanFord(const std::vector<std::vector<int>> &matrix, int start, int target) {
        int n = matrix.size();
        std::vector<int> dist(n, INT_MAX);
        std::vector<int> parent(n, -1);
        dist[start] = 0;

        for (int i = 0; i < n - 1; ++i) {
            for (int u = 0; u < n; ++u) {
                for (int v = 0; v < n; ++v) {
                    if (matrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + matrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // Check for negative weight cycles
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (matrix[u][v] != 0 && dist[u] != INT_MAX && dist[u] + matrix[u][v] < dist[v]) {
                    return "-1";
                }
            }
        }

        return constructPath(parent, start, target);
    }
     std::string Algorithms::constructPath(const std::vector<int> &parent, int start, int target) {
        std::vector<int> path;
        for (int at = target; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
        if (path[0] != start) {
            return "-1"; // Return a message if no path is found
        }

        std::ostringstream oss;
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) {
                oss << "->";
            }
            oss << path[i];
        }
        
        return oss.str();
    }
}
