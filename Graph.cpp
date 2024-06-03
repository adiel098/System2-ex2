//ID:207988213
//E-mail: haleviadiel@gmail.com

#include <iostream>
#include <vector>
#include "Graph.hpp"
#include <ostream>
#include <sstream>

 namespace ariel{

        
        // Default constructor
        Graph::Graph()
        { }

        bool Graph::get_isWeighted()const
        {
            return isWeighted;
        }

        
        bool Graph::get_graphDirected()const
        {
            return isDirected;
        }
        std::vector<std::vector<int>> Graph::get_matrix()const
        {
            return this->adj_Mat;
        }

        
        int Graph::get_countVertices()const
        {
            return countVertices;
        }
        int Graph::get_countEdges()const
        {
            return countEdges;
        }

        

        

        
        std::string Graph::printGraph()
        {

            std::string output;

            for (size_t i = 0; i < get_countVertices(); ++i) {
            output += "[";
            for (size_t j = 0; j < get_matrix()[i].size(); ++j) {
                output += std::to_string(get_matrix()[i][j]);
                if (j < get_matrix()[i].size() - 1) {
                    output += ", ";
                }
            }
            output += "]";
            if (i < get_matrix()[i].size() - 1) {
                output += "\n";
            }
                }

            return output;
        }

        void Graph::loadGraph(const std::vector<std::vector<int>>& adj_Mat)
        {

            countVertices = adj_Mat.size();
            countEdges = 0;
            isDirected=true;
            this->adj_Mat=adj_Mat;

            if(adj_Mat.size() != adj_Mat[0].size())
            {
                throw std::invalid_argument("Invalid graph: The graph is not a square matrix.\n");
            }

            //check if directed
            for(int i=0;i<adj_Mat.size();i++)
            {
                for(int j=0;j<adj_Mat.size();j++)
                        {
                             if(adj_Mat[i][j]!=adj_Mat[j][i])   
                             {
                                isDirected=false;
                             }
                             if(adj_Mat[i][j]!=0)
                             {
                                countEdges++;
                             }
                        }
                
            }
            if(!isDirected)
            {
                countEdges=countEdges/2;
            }
            
        }
        

        Graph Graph:: operator+(const Graph& other) const
        {
            isSameSize(other,*this) ;
            std::vector<std::vector<int>> m1=other.get_matrix();
            std::vector<std::vector<int>> m2=get_matrix();
            int n=m1.size();

            std::vector<std::vector<int>> result(n,std::vector<int>(n,0));

            for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n ;++j) {
                        result[i][j] = m1[i][j] + m2[i][j];
                    }
                }
            Graph g;
            g.loadGraph(result);
            return g;

        }

        void Graph::isSameSize(const Graph& g1,  const Graph& g2) const
        {

        if(g1.get_matrix().size()!=g2.get_matrix().size())
                {
                    throw std::invalid_argument("Invalid opertaion: The graphs are not in the same size.\n");
                }
            
        }
        std::ostream &operator<<(std::ostream& output, const Graph& g)

        {
            Graph g1 =g;
            output<<g1.printGraph();
            return output;
        }

    /// Operator +=
    Graph& Graph::operator+=(const Graph& other) {
        // Convert both graphs to adjacency matrices
        std::vector<std::vector<int>> m1 = get_matrix();
        std::vector<std::vector<int>> m2 = other.get_matrix();
        
        // Make sure the matrices have the same size
        isSameSize(other, *this);

        // Add corresponding elements of 'm2' to 'm1'
        for (size_t i = 0; i < m1.size(); ++i) {
            for (size_t j = 0; j < m1[i].size(); ++j) {
                m1[i][j] += m2[i][j];
            }
        }

        // Load the result back into this graph
        this->loadGraph(m1);

        return *this;
    }

    // Operator -
    Graph Graph::operator-(const Graph& other) const {
        // Convert both graphs to adjacency matrices
        std::vector<std::vector<int>> m1 = get_matrix();
        std::vector<std::vector<int>> m2 = other.get_matrix();

        // Make sure the matrices have the same size
        isSameSize(other, *this);

        // Subtract corresponding elements of 'm2' from 'm1' and create a new graph
        std::vector<std::vector<int>> result(m1.size(), std::vector<int>(m1.size(), 0));
        for (size_t i = 0; i < m1.size(); ++i) {
            for (size_t j = 0; j < m1[i].size(); ++j) {
                result[i][j] = m1[i][j] - m2[i][j];
            }
        }

        Graph g;
        g.loadGraph(result);
        return g;
    }

    // Operator -=
    Graph& Graph::operator-=(const Graph& other) {
        // Convert both graphs to adjacency matrices
        std::vector<std::vector<int>> m1 = get_matrix();
        std::vector<std::vector<int>> m2 = other.get_matrix();

        // Make sure the matrices have the same size
        isSameSize(other, *this);

        // Subtract corresponding elements of 'm2' from 'm1'
        for (size_t i = 0; i < m1.size(); ++i) {
            for (size_t j = 0; j < m1[i].size(); ++j) {
                m1[i][j] -= m2[i][j];
            }
        }

        // Load the result back into this graph
        this->loadGraph(m1);

        return *this;
    }

    // Unary +
    Graph Graph::operator+() const {
        // Unary plus does nothing, simply return a copy of this graph
        return *this;
    }

    // Unary -
    Graph Graph::operator-() const {
        // Convert the graph to an adjacency matrix
        std::vector<std::vector<int>> m = get_matrix();

        // Negate all elements of the adjacency matrix and create a new graph
        std::vector<std::vector<int>> result(m.size(), std::vector<int>(m.size(), 0));
        for (size_t i = 0; i < m.size(); ++i) {
            for (size_t j = 0; j < m[i].size(); ++j) {
                result[i][j] = -m[i][j];
            }
        }

        Graph g;
        g.loadGraph(result);
        return g;
    }
    // Multiplication operator
    Graph Graph::operator*(const Graph& other) const
     {
     isSameSize(other,*this);
         // Convert the graphs to adjacency matrices
    std::vector<std::vector<int>> matrix1 = get_matrix();
    std::vector<std::vector<int>> matrix2 = other.get_matrix();

    
    std::vector<std::vector<int>> resultMatrix(countVertices, std::vector<int>(countVertices, 0));

   
    for (int i = 0; i < countVertices; ++i) {
        for (int j = 0; j < countVertices; ++j) {
            for (int k = 0; k < countVertices; ++k) {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    Graph resultGraph;
    resultGraph.loadGraph(resultMatrix);
    return resultGraph;


    }
    

bool Graph::operator>=(const Graph& other) const {

        return !(*this<other)||*this==other;
}
bool Graph::operator!=(const Graph& other) const {

    return !(*this==other);
}

bool Graph::operator>(const Graph& other) const {

        return !(*this<other)&&!(*this==other);
}

   bool Graph::operator<=(const Graph& other) const {

        return !(*this>other)||*this==other;
}

    
bool Graph::operator<(const Graph& other) const{
        
    std::vector<std::vector<int>> matrix1 = get_matrix();
    std::vector<std::vector<int>> matrix2 = other.get_matrix();
    bool flag =true;
    //we will check if any number in one matrix is < || = the other matrix, to check if contained
    if(*this == other)
        return false;

    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix1[i].size(); ++j) {
            if (matrix1[i][j] >matrix2[i][j]) {
                flag= false; //its contained
            }
        }
    }
    if(flag)
    {
        return true; //G1 < G2
    }
    if(!(*this == other))
    {
        if(this->get_countEdges()<other.get_countEdges())
        {
            return true;
        }
        else if(this->get_countVertices()<other.get_countVertices())
        {
            return true;
        }
        return false;

    }
    return false;
    }
// Operator for checking if one graph is equal to another
bool Graph::operator==(const Graph& other) const {

    // Check if the number of vertices is the same
    if (this->get_countVertices() != other.get_countVertices()) {
        return false;
    }

    std::vector<std::vector<int>> matrix1 = get_matrix();
    std::vector<std::vector<int>> matrix2 = other.get_matrix();

    // Compare the adjacency matrices element-wise
    for (size_t i = 0; i < matrix1.size(); ++i) {
        for (size_t j = 0; j < matrix1[i].size(); ++j) {
            if (matrix1[i][j] != matrix2[i][j]) {
                return false;
            }
        }
    }
    // If the adjacency matrices are the same, return true
    return true;
}



    Graph& Graph::operator++() {
        // Convert the graph to an adjacency matrix
        std::vector<std::vector<int>> m = get_matrix();

        // Increment all elements of the adjacency matrix and load the result back into this graph
        for (size_t i = 0; i < m.size(); ++i) {
            for (size_t j = 0; j < m[i].size(); ++j) {
                ++m[i][j];
            }
        }

        this->loadGraph(m);

        return *this;
    }

    
    Graph Graph::operator++(int) {
        Graph temp(*this);
        ++(*this);
        return temp;
    }

    
    Graph& Graph::operator--() {
        // Convert the graph to an adjacency matrix
        std::vector<std::vector<int>> m = get_matrix();

        // Decrement all elements of the adjacency matrix and load the result back into this graph
        for (size_t i = 0; i < m.size(); ++i) {
            for (size_t j = 0; j < m[i].size(); ++j) {
                --m[i][j];
            }
        }

        this->loadGraph(m);

        return *this;
    }

    
    Graph Graph::operator--(int) {
        Graph temp(*this);
        --(*this);
        return temp;
    }
Graph& Graph::operator/=(int scalar) {
    if (scalar == 0) {
        throw std::invalid_argument("Division by zero");
    }

    std::vector<std::vector<int>> adjMatrix = get_matrix();

    for (size_t i = 0; i < adjMatrix.size(); ++i) {
        for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
            adjMatrix[i][j] /= scalar;
        }
    }

    this->loadGraph(adjMatrix); // Assuming a method to update the graph from an adjacency matrix
    return *this;
}
    Graph Graph::operator*=(int scalar) {
    std::vector<std::vector<int>> adjMatrix = get_matrix();

    for (size_t i = 0; i < adjMatrix.size(); ++i) {
        for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
            adjMatrix[i][j] *= scalar;
        }
    }

    this->loadGraph(adjMatrix); // Assuming a method to update the graph from an adjacency matrix
    return *this;
}
 }







