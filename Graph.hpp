//ID:207988213
//E-mail: haleviadiel@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
namespace ariel
{

    class Graph;

class Graph {
    // Class members and methods
    private:
        bool isDirected=false;
        bool isWeighted=false;  
        int countVertices =0;
        int countEdges =0;
        std::vector<std::vector<int>> adj_Mat;


    public:
        Graph();
        int get_countVertices()const;
        int get_countEdges()const;

        bool get_graphDirected()const;
        std::vector<std::vector<int>> get_matrix()const ;

        bool get_isWeighted()const;
        void loadGraph(const std::vector<std::vector<int>>& adj_Mat);
        std::string printGraph();
        void isSameSize(const Graph& g1,  const Graph& g2) const;

        Graph operator+(const Graph& other) const;
            Graph& operator+=(const Graph& other);
            Graph operator-(const Graph& other) const;
            Graph& operator-=(const Graph& other);
            Graph operator+() const; // Unary +
            Graph operator-() const; // Unary -
            bool operator>(const Graph& other) const;
            bool operator>=(const Graph& other) const;
            bool operator<(const Graph& other) const;
            bool operator<=(const Graph& other) const;
            bool operator==(const Graph& other) const;
            bool operator!=(const Graph& other) const;

            Graph& operator++(); // Prefix increment
            Graph operator++(int); // Postfix increment
            Graph& operator--(); // Prefix decrement
            Graph operator--(int); // Postfix decrement
            Graph operator*(const Graph& other) const; // Postfix decrement
            Graph operator*=(int); // Postfix increment
            Graph& operator/=(int scalar);  
            
            friend std::ostream& operator<<(std::ostream& output, const Graph& g);

};

}

#endif
