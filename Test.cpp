//ID:207988213
//E-mail: haleviadiel@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <vector>
#include <stdexcept>
#include <iostream>


using namespace std;
using namespace ariel;



TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == "1");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == "0");
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
}

TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "0");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "The cycle is: 0->1->2->0");
}

TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
}
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}
TEST_CASE("Test isConnected with additional scenarios") {
    // Test a connected graph with more vertices
    ariel::Graph g;
    vector<vector<int>> connectedGraph = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g.loadGraph(connectedGraph);
    CHECK(ariel::Algorithms::isConnected(g) == "1");

    // Test an empty graph
    ariel::Graph emptyGraph;
    CHECK(ariel::Algorithms::isConnected(emptyGraph) == "1");

    
}

TEST_CASE("Test shortestPath with additional scenarios") {
    // Test a graph with multiple shortest paths between vertices
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->1->3");

    // Test a graph with no path between vertices
    ariel::Graph noPathGraph;
    vector<vector<int>> noPathMatrix = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    noPathGraph.loadGraph(noPathMatrix);
    CHECK(ariel::Algorithms::shortestPath(noPathGraph, 0, 2) == "-1");

    // Test a graph with negative weights
    ariel::Graph negativeWeightGraph;
    vector<vector<int>> negativeWeights = {
        {0, 1, -1},
        {1, 0, 2},
        {-1, 2, 0}};
    negativeWeightGraph.loadGraph(negativeWeights);
    CHECK(ariel::Algorithms::shortestPath(negativeWeightGraph, 0, 2) == "-1");
}

TEST_CASE("Test isContainsCycle with additional scenarios") {
    // Test a graph without a cycle
    ariel::Graph acyclicGraph;
    vector<vector<int>> acyclicMatrix = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}};
    acyclicGraph.loadGraph(acyclicMatrix);
    CHECK(ariel::Algorithms::isContainsCycle(acyclicGraph) == "0");

    // Test a cyclic graph with multiple cycles
    ariel::Graph cyclicGraph;
    vector<vector<int>> cyclicMatrix = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {0, 0, 1, 0}};
    cyclicGraph.loadGraph(cyclicMatrix);
    CHECK(ariel::Algorithms::isContainsCycle(cyclicGraph) == "The cycle is: 0->1->2->0");

    // Test a graph with a self-loop
    ariel::Graph selfLoopGraph;
    vector<vector<int>> selfLoopMatrix = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}};
    selfLoopGraph.loadGraph(selfLoopMatrix);
    CHECK(ariel::Algorithms::isContainsCycle(selfLoopGraph) == "0");
}


TEST_CASE("Test invalid graph with additional scenarios") {
    // Test a non-square graph
    ariel::Graph nonSquareGraph;
    vector<vector<int>> nonSquareMatrix = {
        {0, 1, 0},
        {1, 0, 1}};
    CHECK_THROWS(nonSquareGraph.loadGraph(nonSquareMatrix));

    
}
TEST_CASE("Test graph addition")
    {
        ariel::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        ariel::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
        g2.loadGraph(weightedGraph);
        ariel::Graph g3 = g1 + g2;
        vector<vector<int>> expectedGraph = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}};
        CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    }


    TEST_CASE("Test graph multiplication")
    {
        ariel::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        ariel::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
        g2.loadGraph(weightedGraph);
        ariel::Graph g4 = g1 * g2;
        vector<vector<int>> expectedGraph = {
            {1, 0, 2},
            {1, 3, 1},
            {1, 0, 2}};
        CHECK(g4.printGraph() == "[1, 0, 2]\n[1, 3, 1]\n[1, 0, 2]");
    }

   
    TEST_CASE("Test graph addition")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph1);
        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}};
        g2.loadGraph(graph2);
        ariel::Graph g3 = g1 + g2;
        vector<vector<int>> expectedGraph = {
            {0, 3, 1},
            {3, 0, 4},
            {1, 4, 0}};
        CHECK(g3.printGraph() == "[0, 3, 1]\n[3, 0, 4]\n[1, 4, 0]");
    }


    TEST_CASE("Test graph addition operator+")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
        g2.loadGraph(graph2);

        ariel::Graph g3 = g1 + g2;
        vector<vector<int>> expectedGraph = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}};
        CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    }

    TEST_CASE("Test graph addition operator+=")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
        g2.loadGraph(graph2);

        g1 += g2;
        vector<vector<int>> expectedGraph = {
            {0, 2, 1},
            {2, 0, 3},
            {1, 3, 0}};
        CHECK(g1.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
    }

    TEST_CASE("Test graph subtraction operator-")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 3, 1},
            {3, 0, 4},
            {1, 4, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
        g2.loadGraph(graph2);

        ariel::Graph g3 = g1 - g2;
        vector<vector<int>> expectedGraph = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
        CHECK(g3.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    }

    TEST_CASE("Test graph subtraction operator-=")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 3, 1},
            {3, 0, 4},
            {1, 4, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 1},
            {1, 0, 2},
            {1, 2, 0}};
        g2.loadGraph(graph2);

        g1 -= g2;
        vector<vector<int>> expectedGraph = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
        CHECK(g1.printGraph() == "[0, 2, 0]\n[2, 0, 2]\n[0, 2, 0]");
    }

    TEST_CASE("Test unary plus operator+")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2 = +g1;
        CHECK(g2.printGraph() == g1.printGraph());
    }

    TEST_CASE("Test unary minus operator-")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2 = -g1;
        vector<vector<int>> expectedGraph = {
            {0, -1, 0},
            {-1, 0, -1},
            {0, -1, 0}};
        CHECK(g2.printGraph() == "[0, -1, 0]\n[-1, 0, -1]\n[0, -1, 0]");
    }

    TEST_CASE("Test graph comparison operator>")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g2.loadGraph(graph2);

        CHECK(g1 > g2);
    }

    TEST_CASE("Test graph comparison operator>=")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g2.loadGraph(graph2);

        CHECK(g1 >= g2);
    }

    TEST_CASE("Test graph comparison operator<")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
        g2.loadGraph(graph2);

        CHECK(g1 < g2);
    }

    TEST_CASE("Test graph comparison operator<=")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2;
        vector<vector<int>> graph2 = {
            {0, 2, 0},
            {2, 0, 2},
            {0, 2, 0}};
        g2.loadGraph(graph2);

        CHECK(g1 <= g2);
    }

    TEST_CASE("Test graph comparison operator==")
    {
        ariel::Graph g1;
        vector<vector<int>> graph1 = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph1);

        ariel::Graph g2;
        g2.loadGraph(graph1);

        CHECK(g1 == g2);
    }
TEST_CASE("Test graph comparison operator==")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    g2.loadGraph(graph1);

    CHECK(g1 == g2);

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g3.loadGraph(graph3);

    CHECK(g1 != g3);
}

TEST_CASE("Test graph comparison operator!=")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 != g2);

    ariel::Graph g3;
    g3.loadGraph(graph1);

    CHECK(g1 == g3);
}

TEST_CASE("Test graph comparison operator>")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 > g2);
}

TEST_CASE("Test graph comparison operator>=")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 >= g2);
    CHECK(g1 >= g1); // self comparison should be true
    CHECK(g2 >= g2); // self comparison should be true
}

TEST_CASE("Test graph comparison operator<")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 < g2);
}

TEST_CASE("Test graph comparison operator<=")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g2.loadGraph(graph2);

    CHECK(g1 <= g2);
    CHECK(g1 <= g1); // self comparison should be true
    CHECK(g2 <= g2); // self comparison should be true
}

TEST_CASE("Test graph comparison operator==")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);

    ariel::Graph g2;
    g2.loadGraph(graph1);

    CHECK(g1 == g2);
}
TEST_CASE("Test graph comparison operator< plus *")
{
    ariel::Graph g1;
    vector<vector<int>> graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1);
    g1*=2;
    ariel::Graph g2;
    vector<vector<int>> graph2 = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    g2.loadGraph(graph2);

    
    CHECK(g1 == g2);
        g1/=2;
    CHECK(g1 < g2);
    g1*=3;
    CHECK(g1 > g2);
    }
    TEST_CASE("Test isContainsCycle with multiple -1") {
    // Test a graph without a cycle
    ariel::Graph acyclicGraph;
    vector<vector<int>> acyclicMatrix = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}};
    acyclicGraph.loadGraph(acyclicMatrix);
    CHECK(ariel::Algorithms::isContainsCycle(acyclicGraph) == "0");

    // Test a cyclic graph with multiple cycles
    ariel::Graph cyclicGraph;
    vector<vector<int>> cyclicMatrix = {
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
        {0, 0, 1, 0}};
    cyclicGraph.loadGraph(cyclicMatrix);
    CHECK(ariel::Algorithms::isContainsCycle(cyclicGraph) == "The cycle is: 0->1->2->0");
    CHECK(ariel::Algorithms::negativeCycle(cyclicGraph) == "No negative cycle found.");

    cyclicGraph*=-1;
     CHECK(ariel::Algorithms::negativeCycle(cyclicGraph) == "Negative cycle found.");

    cyclicGraph.printGraph();

    CHECK(cyclicGraph.printGraph() == "[0, -1, -1, 0]\n[-1, 0, -1, 0]\n[-1, -1, 0, -1]\n[0, 0, -1, 0]");

    // CHECK(ariel::Algorithms::isContainsCycle(cyclicGraph) == "0");
}
    TEST_CASE("Test Negative cycle") {

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 2, 0},
        {0, 0, 1},
        {-4, 0, 0}
       
    };
    g3.loadGraph(graph3);
    CHECK(ariel::Algorithms::negativeCycle(g3) == "Negative cycle found.");

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0}
    };
    g4.loadGraph(graph4);
    CHECK(ariel::Algorithms::negativeCycle(g4) == "No negative cycle found.");
    // Test an empty graph
    ariel::Graph emptyGraph;
    CHECK(ariel::Algorithms::isConnected(emptyGraph) == "1");
    }
    TEST_CASE("Test empty with + operator" ) {
            ariel::Graph cyclicGraph;

    vector<vector<int>> cyclicMatrix = {
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 0, 1},
            {0, 0, 1, 0}};
        cyclicGraph.loadGraph(cyclicMatrix);
        
        ariel::Graph cyclicGraph1;

    vector<vector<int>> cyclicMatrix1 = {
            {0, 1, 1, 0},
            {1, 0, 1, 0},
            {1, 1, 0, 1},
            {0, 0, 1, 0}};
        cyclicGraph1.loadGraph(cyclicMatrix1);

    cyclicGraph*=-1;
    CHECK(cyclicGraph.printGraph() == "[0, -1, -1, 0]\n[-1, 0, -1, 0]\n[-1, -1, 0, -1]\n[0, 0, -1, 0]");

    ariel::Graph emptyGraph;
    // emptyGraph+=  cyclicGraph;
    cyclicGraph+=cyclicGraph1;
    // CHECK_THROWS(emptyGraph.printGraph() == "Invalid opertaion: The graphs are not in the same size.");
    CHECK(cyclicGraph.printGraph() == "[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]\n[0, 0, 0, 0]");




    }
