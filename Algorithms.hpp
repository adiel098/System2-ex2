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

            static std::string isConnected(const Graph g);
            static std::string shortestPath(const Graph& graph, int source, int destination); 
            static std::string isContainsCycle( const Graph g) ;
            static std::string isBipartite( Graph g);
            static std::string negativeCycle( const Graph& g);
            



        private:

            // static bool dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, int start);
            static void dfs(const std::vector<std::vector<int>> &matrix, std::vector<bool> &visited, int start) ;
            static bool isUnweighted(const std::vector<std::vector<int>> &matrix) ;
            static bool hasCycleDFS(const std::vector<std::vector<int>>& graph, std::vector<bool>& visited, std::vector<int>& path, int node, int parent, std::string &cycle);
            static  std::string bfsShortestPath(const std::vector<std::vector<int>> &matrix, int start, int target);
            static std::string dijkstra(const std::vector<std::vector<int>> &matrix, int start, int target) ;
            static  std::string constructPath(const std::vector<int> &parent, int start, int target) ;
            static std::string bellmanFord(const std::vector<std::vector<int>> &matrix, int start, int target) ;
            static bool hasNegativeWeights(const std::vector<std::vector<int>> &matrix) ;
            
            


    };
    



}

