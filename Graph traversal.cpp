#include <bits/stdc++.h>
using namespace std;

class Vertex
{
public:
    int val;
};

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

/* Breadth-first traversal */
// Use adjacency list to represent the graph, to obtain all adjacent vertices of a specified vertex
vector<Vertex *> graphBFS(GraphAdjList &graph, Vertex *startVet)
{
    // Vertex traversal sequence
    vector<Vertex *> res;
    // Hash set, used to record visited vertices
    unordered_set<Vertex *> visited = {startVet};
    // Queue used to implement BFS
    queue<Vertex *> que;
    que.push(startVet);
    // Starting from vertex vet, loop until all vertices are visited
    while (!que.empty())
    {
        Vertex *vet = que.front();
        que.pop();          // Dequeue the vertex at the head of the queue
        res.push_back(vet); // Record visited vertex
        // Traverse all adjacent vertices of that vertex
        for (auto adjVet : graph.adjList[vet])
        {
            if (visited.count(adjVet))
                continue;            // Skip already visited vertices
            que.push(adjVet);        // Only enqueue unvisited vertices
            visited.emplace(adjVet); // Mark the vertex as visited
        }
    }
    // Return the vertex traversal sequence
    return res;
}

/* Depth-first traversal helper function */
void dfs(GraphAdjList &graph, unordered_set<Vertex *> &visited, vector<Vertex *> &res, Vertex *vet)
{
    res.push_back(vet);   // Record visited vertex
    visited.emplace(vet); // Mark the vertex as visited
    // Traverse all adjacent vertices of that vertex
    for (Vertex *adjVet : graph.adjList[vet])
    {
        if (visited.count(adjVet))
            continue; // Skip already visited vertices
        // Recursively visit adjacent vertices
        dfs(graph, visited, res, adjVet);
    }
}

/* Depth-first traversal */
// Use adjacency list to represent the graph, to obtain all adjacent vertices of a specified vertex
vector<Vertex *> graphDFS(GraphAdjList &graph, Vertex *startVet)
{
    // Vertex traversal sequence
    vector<Vertex *> res;
    // Hash set, used to record visited vertices
    unordered_set<Vertex *> visited;
    dfs(graph, visited, res, startVet);
    return res;
}