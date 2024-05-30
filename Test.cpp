    #include "doctest.h"
    #include "Algorithms.hpp"
    #include "Graph.hpp"

    using namespace std;
    using namespace ariel;

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

    TEST_CASE("Invalid operations")
    {
        ariel::Graph g1;
        vector<vector<int>> graph = {
            {0, 1, 0},
            {1, 0, 1},
            {0, 1, 0}};
        g1.loadGraph(graph);
        ariel::Graph g2;
        vector<vector<int>> weightedGraph = {
            {0, 1, 1, 1},
            {1, 0, 2, 1},
            {1, 2, 0, 1}};
        CHECK_THROWS(g2.loadGraph(weightedGraph));
        ariel::Graph g5;
        vector<vector<int>> graph2 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}};
        g5.loadGraph(graph2);
        CHECK_THROWS(g5 * g1);
        CHECK_THROWS(g1 * g2);

        //Addition of two graphs with different dimensions
        ariel::Graph g6;
        vector<vector<int>> graph3 = {
            {0, 1, 0, 0, 1},
            {1, 0, 1, 0, 0},
            {0, 1, 0, 1, 0},
            {0, 0, 1, 0, 1},
            {1, 0, 0, 1, 0}};
        g6.loadGraph(graph3);
        CHECK_THROWS(g1 + g6);
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
    
}
