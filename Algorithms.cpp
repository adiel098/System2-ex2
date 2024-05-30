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

using namespace std;

namespace ariel
{


string Algorithms::isConnected(Graph g)
{
   if (g.get_countVertices()<=1)
    
   {
    return "1";
   }
   
    std::vector<bool> visited(g.get_countVertices(), false);
    Vertex& v = g.get_vertex(0);
    DFS(v,visited);

    for (bool isVisited : visited) 
    {
        if (!isVisited ) 
        {
            return "0"; // Graph is not connected
        }
    }

    return "1";

}

std::string Algorithms::shortestPath(Graph g, int start, int end) {
    if (g.get_isWeighted()) {
        // Calculate shortest path using Dijkstra's algorithm
        std::vector<int> shortestDistance = Dijkstra(g, start, end);
        if (!shortestDistance.empty()) {
            // Construct the path string
            std::string path;
            for (int i = 0; i < shortestDistance.size() - 1; i++) {
                path += std::to_string(shortestDistance[i]) + "->";
            }
            path += std::to_string(shortestDistance.back()); // Append last vertex
            return path;
        } else {
            return "There is no path from vertex " + std::to_string(start) + " to vertex " + std::to_string(end);
        }
    } else {
        // Calculate shortest path using BFS algorithm
        std::vector<int> shortestPath = BFS(g, start, end);
        if (shortestPath.empty()) {
            return "-1"; // No path found
        } else {
            // Construct the path string
            std::string path;
            for (int i = 0; i < shortestPath.size() - 1; i++) {
                path += std::to_string(shortestPath[i]) + "->";
            }
            path += std::to_string(shortestPath.back()); // Append last vertex
            return path;
        }
    }
}


string Algorithms::isContainsCycle(Graph g)
{

     std::vector<bool> visited(g.get_countVertices(), false);
     std::vector<int> parent(g.get_countVertices(),-1);
     std::vector<Vertex> cycle;
    stringstream result1;

     for (Vertex v : g.get_graphVertices()) 
     {
            if (!visited[v.get_data()]) 
            {
                if (isCyclic(v, visited, parent, cycle))
                 {
                    // Print the cycle
                    result1 << "The cycle is: ";
                    for (int i = cycle.size() - 2; i > 0; --i) 
                    {
                        result1 << cycle[i].get_data() << "->";
                    }
                    result1 << cycle[0].get_data() << "->";
                    result1 << cycle[cycle.size()-1].get_data();

                    return result1.str();
                }
            }
        }

        //no cycle was found
        return "0";


}



string Algorithms::negativeCycle( Graph g)
{
    stringstream str;
     bool foundNegativeCycle = false;
        for (int i = 0; i < g.get_countVertices(); ++i) 
        {
            Vertex v = g.get_vertex(i);
            if (hasNegativeCycle(g,v)) 
            {
                foundNegativeCycle = true;
            }
        }
        if (!foundNegativeCycle) 
        {
            str << "No negative cycles found in the graph." << endl;
        }
        else
        {
            str << "There exist a negtive cycle !" << endl;
        }
        return str.str();

}




// Breadth-First Search (BFS) function to find the shortest path in a graph
vector<int> Algorithms::BFS(Graph g, int source, int destination) 
{
    // Get the number of vertices in the graph
    int n = g.get_countVertices();

    // Queue for BFS
    queue<int> que;

    // Vector to store the parent of each vertex in the shortest path
    vector<int> parent(n, -1); 

    // Vector to keep track of visited vertices
    vector<bool> visited(n, false);

    // Start BFS from the source vertex
    que.push(source);
    visited[source] = true;

    // Continue the search while there are vertices in the queue
    while (!que.empty()) 
    {
        // Get the current vertex from the queue
        int current = que.front();
        que.pop();

        // If the destination vertex is reached, construct the shortest path
        if (current == destination) 
        {
            // Vector to store the shortest path
            vector<int> shortestPath;

            // Trace the path from destination to source using the parent vector
            while (current != -1) {
                shortestPath.push_back(current);
                current = parent[current];
            }

            // Reverse the path to get it from source to destination
            reverse(shortestPath.begin(), shortestPath.end());
            return shortestPath;
        }

        // Explore the neighbours of the current vertex
        for (Edge e : g.get_vertex(current).get_Neighbours()) 
        {
            // If the neighbour has not been visited
            if (!visited[e.get_dest().get_data()]) 
            {
                // Mark the neighbour as visited
                visited[e.get_dest().get_data()] = true;

                // Set the parent of the neighbour to the current vertex
                parent[e.get_dest().get_data()] = current;

                // Add the neighbour to the queue for further exploration
                que.push(e.get_dest().get_data());
            }
        }
    }

    // No path found from source to destination
    return {};
}
// Depth-First Search (DFS) function for traversing a graph
void Algorithms::DFS(Vertex& v, std::vector<bool>& visited)
{
    // Mark the current vertex as visited
    visited[v.get_data()] = true;

    // Get the number of neighbours of the current vertex
    int size = v.get_Neighbours().size();

    // Iterate over each neighbour (edge) of the current vertex
    for(Edge& e : v.get_Neighbours())
    {
        // If the destination vertex of the edge has not been visited
        if(!visited[e.get_dest().get_data()])
        {
            // Recursively perform DFS on the destination vertex
            DFS(e.get_dest(), visited);
        }
    }
}

    // Dijkstra's algorithm to find the shortest distance from source to destination
std::vector<int> Algorithms::Dijkstra(Graph g, int source, int destination) 
{
    // Initialize distances to all vertices as infinity
    std::vector<int> dist(g.get_countVertices(), INT_MAX);
    dist[source] = 0;

    // Array to store parent vertices
    std::vector<int> parent(g.get_countVertices(), -1);

    // Priority queue to store vertices based on their distances
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (u == destination) 
        {

            // Construct path from source to destination using before array
            std::vector<int> shortestPath;
            int current = destination;
            while (current != -1) 
            {
                shortestPath.push_back(current);
                current = parent[current];
            }
            std::reverse(shortestPath.begin(), shortestPath.end());
            return shortestPath;
        }

        // Traverse all adjacent vertices of u
        for (Edge edge : g.get_vertex(u).get_Neighbours()) 
        {
            int v = edge.get_dest().get_data();
            int weight = edge.get_weight();

            // Relaxation method
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) 
            {
                dist[v] = dist[u] + weight;
                parent[v] = u; // Update predecessor of v
                pq.push({dist[v], v});
            }
        }
    }

    // Destination not reachable from source
    return std::vector<int>(); 
}



 bool Algorithms::isCyclic(Vertex v, std::vector<bool>& visited, std::vector<int>& parent, std::vector<Vertex>& cycle) 
 {
        int v_data = v.get_data();
        visited[v.get_data()] = true; // Mark current vertex as visited
        

        // run by Recursion for all vertices near to this vertex
        for (Edge e : v.get_Neighbours()) 
        {
            size_t vertex_id = e.get_dest().get_data();
            if (!visited[vertex_id]) 
            {
                parent[vertex_id] = v_data;
                if (isCyclic(e.get_dest(), visited, parent, cycle))
                    return true;
            } 
            else if (e.get_dest().get_data() != parent[v.get_data()]) 
            {
                // Cycle is found, backtrack to find the whole cycle
                cycle.push_back(v);
                Vertex cur = v;
                while (cur.get_data() != vertex_id ) 
                {
                    cur = parent[cur.get_data()];
                    cycle.push_back(cur);
                }
                cycle.push_back(e.get_dest());
                return true;
            }
        }
        return false;
}


 // Check for negative cycles using Bellman-Ford algorithm
bool Algorithms::hasNegativeCycle(Graph g,Vertex src) 
{
        std::vector<int> dist(g.get_countVertices(), INT_MAX);
        dist[src.get_data()] = 0;

        // Relax method for all edges 
        for (size_t i=0;i<g.get_countVertices()-1;i++) 
        {
            Vertex v = g.get_vertex(i);

            for (Edge edge : v.get_Neighbours()) 
            {
                if (dist[edge.get_dest().get_data()] != INT_MAX && dist[edge.get_dest().get_data()] > dist[v.get_data()] + edge.get_weight()) 
                {
                    dist[edge.get_dest().get_data()] = dist[v.get_data()] + edge.get_weight();
                }
            }
        }

        /*
        Check for negative cycles.
        If at iteration |V|-(number of vertices) there is still a possible relax-a negative cycle is exist.
        */ 
        
        Vertex v = g.get_vertex(g.get_countVertices()-1);

        for (Edge edge : v.get_Neighbours())
        {
            if (dist[v.get_data()] != INT_MAX && dist[edge.get_dest().get_data()] > dist[v.get_data()] + edge.get_weight()) 
            {
                return true; // Negative cycle found
            }
        }


        
       
        return false; // No negative cycle found
}

string Algorithms::isBipartite(Graph g) 
{
    int size = g.get_countVertices();
    vector<int> color(size, 0); // 0: not colored, 1: color 1, -1: color 2
    queue<int> q;
    queue<int> empty;
    swap(q, empty);

    for (int i = 0; i < size; ++i)
     {
        if (color[i] != 0) continue; // Already colored/visited
        q.push(i);
        color[i] = 1;

        while (!q.empty()) {
            int curr = q.front();
            q.pop();

            for (Edge e : g.get_vertex(curr).get_Neighbours()) 
            {
                if (color[e.get_dest().get_data()] == 0) 
                { // Not colored yet
                    color[e.get_dest().get_data()] = -color[curr]; // Assign opposite color
                    q.push(e.get_dest().get_data());
                } else if (color[e.get_dest().get_data()] == color[curr])
                 { // Conflict
                    return "0"; // Graph is not bipartite
                }
            }
        }
    }

    vector<int> group1, group2;

    for (int i = 0; i < size; ++i) {
        if (color[i] == 1) {
            group1.push_back(i);
        } else {
            group2.push_back(i);
        }
    }

    stringstream result;
    result << "The graph is bipartite: A={";
    for (int i=0;i<group1.size()-1;i++) 
    {
        result  << group1[i] << ", ";
    }
    result  << group1[group1.size()-1];
    result  << "},";

    result  << " B={";
    for (int j=0; j<group2.size()-1;j++) {
        result << group2[j] << ", ";
    }
    result << group2[group2.size()-1];
    result << "}";
    
    group1.clear();
    group2.clear();


    return result.str(); // Graph is bipartite
}

}
