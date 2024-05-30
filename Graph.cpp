//ID:207988213
    //E-mail: haleviadiel@gmail.com

    #include <iostream>
    #include <vector>
    #include "Graph.hpp"
    #include <sstream>
    #include <ostream>

    namespace ariel{

            // Default constructor
            Vertex::Vertex() 
            {}


            Vertex::Vertex(int data)
            {this->data =data;}


        int Vertex::get_data() const
        {
            return data;
        }


            std::vector<Edge>& Vertex::get_Neighbours()
            {
                return this->neighbours;
            }
            const std::vector<Edge>& Vertex::get_Neighbours() const        
            {
                return this->neighbours;
            }

            // Default constructor
            Edge::Edge()
            {}
            
            Edge::Edge(Vertex& dest,int weight)
            {
                this->dest = &dest;
                this-> weight = weight;
            }


            int Edge::get_weight()const
            {
                return weight;
            }
            Vertex& Edge::get_dest()const
            {
                return *dest;
            }   
            // Default constructor
            Graph::Graph()
            { }

            bool Graph::get_isWeighted()
            {
                return isWeighted;
            }

            Vertex& Graph::get_vertex(int data)
            {
                if (data >= 0 && data < vertices.size()) 
                {
                    return vertices[data];
                } 
                else 
                {  
                    throw std::out_of_range("Index out of range");
                    // or return nullptr;
                }
            }
            std::vector<Vertex>Graph::get_graphVertices()
            {
                return vertices;
            }
            bool Graph::get_graphDirected()
            {
                return isDirected;
            }

            void Graph::set_graphDirected(bool flag)
            {
                this->isDirected = flag;
            }
            int Graph::get_countVertices()const
            {
                return countVertices;
            }
            int Graph::get_countEdges()const
            {
                return countEdges;

            }

            void Graph::set_isWeighted(bool flag)
            {
                this->isWeighted = flag;
            }

            void Graph::add_Neighbour(Vertex& source,Vertex& destination,int weight)
            {
                if(source.get_data() < vertices.size())
                {
                    Edge* e =  new Edge(destination,weight);
                    vertices[source.get_data()].get_Neighbours().push_back(*e);
                    countEdges++;

                }
                else
                {
                    throw std::out_of_range("Source index out of range");
                }
                
            }

            void Graph::add_Vertex(Vertex v)
            {
                vertices.push_back(v);
                countVertices++;

            }
            std::string Graph::printGraph()
            {
            std::string output;
            
            for (size_t i = 0; i < vertices.size(); ++i) {
                const auto& row = vertices[i].get_Neighbours();
                output += "[";
                for (size_t j = 0; j < row.size(); ++j) {
                    output += std::to_string(row[j].get_weight());
                    if (j < row.size() - 1) {
                        output += ", ";
                    }
                }
                output += "]";
                if (i < vertices.size() - 1) {
                    output += "\n";
                }
            }
            
            return output;
        
            }

            void Graph::loadGraph(const std::vector<std::vector<int>>& adj_Mat)
            {
                countVertices = 0;
                countEdges = 0;
                isWeighted = false;
                vertices.clear(); 
                if(adj_Mat.size() != adj_Mat[0].size())
                {
                    throw std::invalid_argument("Invalid graph: The graph is not a square matrix.\n");
                }

                // Use 'this' pointer to access the current object
                for (size_t i = 0; i < adj_Mat.size(); i++)
                {
                    Vertex* v = new Vertex(i);
                    this->add_Vertex(*v);
                }

                for (size_t j = 0; j < adj_Mat.size(); j++)
                {
                    Vertex& source = this->get_vertex(j);
                    for (size_t k = 0; k < adj_Mat.size(); k++)
                    {
                        if (adj_Mat[j][k] > 1)
                        {
                            this->set_isWeighted(true);
                        }

                        if(adj_Mat[j][k] !=adj_Mat[k][j])
                        {
                            set_graphDirected(true);
                        } 
                        
                    
                            
                                Vertex& dest = this->get_vertex(k);
                            this->add_Neighbour(source, dest, adj_Mat[j][k]);
                            
                        }
                        
                    
                    }
                
            }
            

        Graph Graph:: operator+(const Graph& other) const
        {
            isSameSize(other,*this) ;
            std::vector<std::vector<int>> m1=toAdjacencyMatrix(other);
            std::vector<std::vector<int>> m2=toAdjacencyMatrix(*this);
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

        if(g1.get_countVertices()!=g2.get_countVertices())
                {
                    throw std::invalid_argument("Invalid opertaion: The graphs are not in the same size.\n");
                }
            
        }
        
        std::vector<std::vector<int>> Graph::toAdjacencyMatrix(const Graph &g) const
        {
            std::vector<std::vector<int>> adjMatrix(g.get_countVertices(), std::vector<int>(g.get_countVertices(), 0));

            for (const Vertex& v : g.vertices) {
                int srcIdx = v.get_data();
                for (const Edge& e : v.get_Neighbours()) {
                    int destIdx = e.get_dest().get_data();
                    adjMatrix[srcIdx][destIdx] = e.get_weight();
                }
            }

            return adjMatrix;
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
        std::vector<std::vector<int>> m1 = toAdjacencyMatrix(*this);
        std::vector<std::vector<int>> m2 = toAdjacencyMatrix(other);
        
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
        std::vector<std::vector<int>> m1 = toAdjacencyMatrix(*this);
        std::vector<std::vector<int>> m2 = toAdjacencyMatrix(other);

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
        std::vector<std::vector<int>> m1 = toAdjacencyMatrix(*this);
        std::vector<std::vector<int>> m2 = toAdjacencyMatrix(other);

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
        std::vector<std::vector<int>> m = toAdjacencyMatrix(*this);

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
    std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
    std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);

    
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
        
    std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
    std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);
    bool flag =true;
    //we will check if any number in one matrix is < || = the other matrix, to check if contained
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

    std::vector<std::vector<int>> matrix1 = toAdjacencyMatrix(*this);
    std::vector<std::vector<int>> matrix2 = toAdjacencyMatrix(other);

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
        std::vector<std::vector<int>> m = toAdjacencyMatrix(*this);

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
        std::vector<std::vector<int>> m = toAdjacencyMatrix(*this);

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

    std::vector<std::vector<int>> adjMatrix = toAdjacencyMatrix(*this);

    for (size_t i = 0; i < adjMatrix.size(); ++i) {
        for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
            adjMatrix[i][j] /= scalar;
        }
    }

    this->loadGraph(adjMatrix); // Assuming a method to update the graph from an adjacency matrix
    return *this;
}
    Graph Graph::operator*=(int scalar) {
    std::vector<std::vector<int>> adjMatrix = toAdjacencyMatrix(*this);

    for (size_t i = 0; i < adjMatrix.size(); ++i) {
        for (size_t j = 0; j < adjMatrix[i].size(); ++j) {
            adjMatrix[i][j] *= scalar;
        }
    }

    this->loadGraph(adjMatrix); // Assuming a method to update the graph from an adjacency matrix
    return *this;
}
    }


