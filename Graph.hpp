//ID:207988213
//E-mail: haleviadiel@gmail.com

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
namespace ariel
{

    class Edge;
    class Vertex;
    class Graph;


class Vertex {
    
    private:
        std::vector<Edge> neighbours;   
        int data;

    public:
        Vertex();
        Vertex(int data);
        int get_data() const;
        const std::vector<Edge>& get_Neighbours() const ;
        std::vector<Edge>& get_Neighbours() ;
      

};

class Edge{

    private:
        Vertex* dest;
        int weight;

    public:
        Edge();
        Edge(Vertex& dest,int weight);
        Vertex& get_dest()const;
        int get_weight()const;

};

class Graph {
    // Class members and methods
    private:
        bool isDirected=false;
        bool isWeighted=false;  

        int countVertices =0;
        int countEdges =0;
        std::vector<Vertex> vertices;

    public:
        Graph();
        std::vector<Vertex>  get_graphVertices();
        Vertex& get_vertex(int data);

        int get_countVertices() const;
        int get_countEdges() const;

        bool get_graphDirected();
        void set_graphDirected(bool flag);
        void isSameSize(const Graph& g1,  const Graph& g2) const;

        void set_isWeighted(bool flag);
        bool get_isWeighted();
        void add_Vertex(Vertex v);
        void add_Neighbour(Vertex& source,Vertex& dest,int weight);
        void loadGraph(const std::vector<std::vector<int>>& adj_Mat);
        std::string printGraph();  
        std::vector<std::vector<int>>toAdjacencyMatrix(const Graph& other) const;
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
