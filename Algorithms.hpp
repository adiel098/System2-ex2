//ID:207988213
//E-mail: haleviadiel@gmail.com

#pragma once

#include <string>
#include <vector>
#include "Graph.hpp"




namespace ariel
{
    class Algorithms
    {
        public:

            static std::string isConnected( Graph g);
            static std::string shortestPath( Graph g,int start,int end);
            static std::string isContainsCycle( Graph g);
            static std::string isBipartite( Graph g);
            static std::string negativeCycle( Graph g);
            
        private:
        static void DFS(Vertex& v, std::vector<bool>& visited);
            static std::vector<int> BFS(Graph g,int source, int destination); 
            static std::vector<int> Dijkstra(Graph g, int source, int destination); 
            static bool isCyclic(Vertex v, std::vector<bool>& visited, std::vector<int>& parent, std::vector<Vertex>& cycle); 
            static bool hasNegativeCycle(Graph g,Vertex src);   


    };
    



}

