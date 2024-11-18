#include <iostream>
#include <queue>
#include <vector>
#include <map>
using namespace std;


void bfs(vector<vector<int> >& adjList, int startNode,
         vector<bool>& visited)
{
    queue<int> q;

    // current node as visited and enqueue it
    visited[startNode] = true;
    q.push(startNode);

    // Iterat queue
    while (!q.empty()) {
        // Dequeue a vertex from queue and print it
        int currentNode = q.front();
        q.pop();
        cout << currentNode << " ";

    
        for (size_t i = 0; i < adjList[currentNode].size(); ++i) {
            int neighbor = adjList[currentNode][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// Function to add an edge to the graph
void addEdge(vector<vector<int> >& adjList, int u, int v)
{
    adjList[u].push_back(v);
}

int main()
{
    int vertices = 5;

    vector<vector<int> > adjList(vertices);

    // Add edges to the graph
    addEdge(adjList, 0, 1);
    addEdge(adjList, 0, 2);
    addEdge(adjList, 1, 3);
    addEdge(adjList, 1, 4);
    addEdge(adjList, 2, 4); // Mark all the vertices as not visited
    vector<bool> visited(vertices, false);

    cout << "Breadth First Traversal starting from vertex 0: ";
    bfs(adjList, 0, visited);

    return 0;
}




















//class Graph {
//public:
//    map<int, bool> visited;
//    map<int, list<int> > adj;
//
//    // Function to add an edge to graph
//    void addEdge(int v, int w);
//

//    void DFS(int v);
//};
//
//void Graph::addEdge(int v, int w)
//{
//    // Add w to v’s list.
//    adj[v].push_back(w);
//    adj[w].push_back(v);
//}
//
//void Graph::DFS(int v)
//{
//    // Mark the current node as visited and
//    // print it
//    visited[v] = true;
//    cout << v << " ";
//
//    // Recur for all the vertices adjacent
//    // to this vertex
//    list<int>::iterator i;
//    for (i = adj[v].begin(); i != adj[v].end(); ++i)
//        if (!visited[*i])
//            DFS(*i);
//}
//
//int main()
//{
//    // Create a graph given in the above diagram
//    Graph g;
//    g.addEdge(0, 1);
//    g.addEdge(0, 2);
//    g.addEdge(1, 2);
//    g.addEdge(2, 0);
//    g.addEdge(2, 3);
//    g.addEdge(3, 3);
//
//    cout << "Following is Depth First Traversal"
//            " (starting from vertex 2) \n";
//
//    // Function call
//    g.DFS(2);
//
//    return 0;
//}

