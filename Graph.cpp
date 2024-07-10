#include <bits/stdc++.h>
using namespace std;

/* Undirected graph class based on adjacency matrix */
class GraphAdjMat
{
    vector<int> vertices;       // Vertex list, elements represent "vertex value", index represents "vertex index"
    vector<vector<int>> adjMat; // Adjacency matrix, row and column indices correspond to "vertex index"

public:
    /* Constructor */
    GraphAdjMat(const vector<int> &vertices, const vector<vector<int>> &edges)
    {
        // Add vertex
        for (int val : vertices)
        {
            addVertex(val);
        }
        // Add edge
        // Edges elements represent vertex indices
        for (const vector<int> &edge : edges)
        {
            addEdge(edge[0], edge[1]);
        }
    }

    /* Get the number of vertices */
    int size() const
    {
        return vertices.size();
    }

    /* Add vertex */
    void addVertex(int val)
    {
        int n = size();
        // Add new vertex value to the vertex list
        vertices.push_back(val);
        // Add a row to the adjacency matrix
        adjMat.emplace_back(vector<int>(n, 0));
        // Add a column to the adjacency matrix
        for (vector<int> &row : adjMat)
        {
            row.push_back(0);
        }
    }

    /* Remove vertex */
    void removeVertex(int index)
    {
        if (index >= size())
        {
            throw out_of_range("Vertex does not exist");
        }
        // Remove vertex at `index` from the vertex list
        vertices.erase(vertices.begin() + index);
        // Remove the row at `index` from the adjacency matrix
        adjMat.erase(adjMat.begin() + index);
        // Remove the column at `index` from the adjacency matrix
        for (vector<int> &row : adjMat)
        {
            row.erase(row.begin() + index);
        }
    }

    /* Add edge */
    // Parameters i, j correspond to vertices element indices
    void addEdge(int i, int j)
    {
        // Handle index out of bounds and equality
        if (i < 0 || j < 0 || i >= size() || j >= size() || i == j)
        {
            throw out_of_range("Vertex does not exist");
        }
        // In an undirected graph, the adjacency matrix is symmetric about the main diagonal, i.e., satisfies (i, j) == (j, i)
        adjMat[i][j] = 1;
        adjMat[j][i] = 1;
    }

    /* Remove edge */
    // Parameters i, j correspond to vertices element indices
    void removeEdge(int i, int j)
    {
        // Handle index out of bounds and equality
        if (i < 0 || j < 0 || i >= size() || j >= size() || i == j)
        {
            throw out_of_range("Vertex does not exist");
        }
        adjMat[i][j] = 0;
        adjMat[j][i] = 0;
    }

    void printVector(vector<int> vertices)
    {
        for (int vertice : vertices)
        {
            cout << vertice << ' ';
        }
    }

    void printVectorMatrix(vector<vector<int>>)
    {
        for (vector<int> row : adjMat)
        {
            for (int element : row)
            {
                cout << setw(3) << element;
            }
            cout << endl;
        }
    }

    /* Print adjacency matrix */
    void print()
    {
        cout << "Vertex list = ";
        printVector(vertices);
        cout << "Adjacency matrix =" << endl;
        printVectorMatrix(adjMat);
    }
};

class Vertex
{
public:
    int val;
};

/* Undirected graph class based on adjacency list */
class GraphAdjList
{
public:
    // Adjacency list, key: vertex, value: all adjacent vertices of that vertex
    unordered_map<Vertex *, vector<Vertex *>> adjList;

    /* Remove a specified node from vector */
    void remove(vector<Vertex *> &vec, Vertex *vet)
    {
        for (int i = 0; i < vec.size(); i++)
        {
            if (vec[i] == vet)
            {
                vec.erase(vec.begin() + i);
                break;
            }
        }
    }

    /* Constructor */
    GraphAdjList(const vector<vector<Vertex *>> &edges)
    {
        // Add all vertices and edges
        for (const vector<Vertex *> &edge : edges)
        {
            addVertex(edge[0]);
            addVertex(edge[1]);
            addEdge(edge[0], edge[1]);
        }
    }

    /* Get the number of vertices */
    int size()
    {
        return adjList.size();
    }

    /* Add edge */
    void addEdge(Vertex *vet1, Vertex *vet2)
    {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
            throw invalid_argument("Vertex does not exist");
        // Add edge vet1 - vet2
        adjList[vet1].push_back(vet2);
        adjList[vet2].push_back(vet1);
    }

    /* Remove edge */
    void removeEdge(Vertex *vet1, Vertex *vet2)
    {
        if (!adjList.count(vet1) || !adjList.count(vet2) || vet1 == vet2)
            throw invalid_argument("Vertex does not exist");
        // Remove edge vet1 - vet2
        remove(adjList[vet1], vet2);
        remove(adjList[vet2], vet1);
    }

    /* Add vertex */
    void addVertex(Vertex *vet)
    {
        if (adjList.count(vet))
            return;
        // Add a new linked list to the adjacency list
        adjList[vet] = vector<Vertex *>();
    }

    /* Remove vertex */
    void removeVertex(Vertex *vet)
    {
        if (!adjList.count(vet))
            throw invalid_argument("Vertex does not exist");
        // Remove the vertex vet's corresponding linked list from the adjacency list
        adjList.erase(vet);
        // Traverse other vertices' linked lists, removing all edges containing vet
        for (auto &adj : adjList)
        {
            remove(adj.second, vet);
        }
    }

    void printVector(vector<int> vec)
    {
        for (int i : vec)
        {
            cout << i << ' ';
        }
    }

    vector<int> vetsToVals(vector<Vertex *> vec)
    {
        vector<int> v;
        for (Vertex *vertex : vec)
        {
            v.push_back(vertex->val);
        }
        return v;
    }

    /* Print the adjacency list */
    void print()
    {
        cout << "Adjacency list =" << endl;
        for (auto &adj : adjList)
        {
            const auto &key = adj.first;
            const auto &vec = adj.second;
            cout << key->val << ": ";
            printVector(vetsToVals(vec));
        }
    }
};

/*                                             Comparision
                            Adjacency matrix            Adjacency list (Linked list)
Determine adjacency             O(1)                               O(m)
Add an edge                     O(1)                               O(1)
Remove an edge                  O(1)                               O(m)
Add a vertex                    O(n)                               O(1)
Remove a vertex                 O(n^2)                             O(n + m)
Memory space usage              O(n^2)                             O(n + m)
*/
