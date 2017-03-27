#include <iostream>
#include <string.h>
#include <climits>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1

using namespace std;

typedef struct edge_s
{
    int node1; // start node
    int node2; // node pointed
    int value; // size of the edge
} edge_t;

typedef struct node_s
{
    int * edges; // linked edges index
    int nbEdges; // number of linked edges
    int value; // dist from start
    int visited; // is this node visited?
} node_t;

int n; // number of nodes
int m; // number of edges
edge_t ** edges; // graph edges
node_t ** nodes; // graph nodes

/* return 1 if the value is into the array, 0 else
*/
int find(int * array, int lenArray, int value)
{
    FOR(i, lenArray)
        if(array[i] == value)
            return 1;
    return 0;
}

void removeShortestPath()
{
    FOR(i, n)
    {
        node_t * nd = nodes[i];
        FOR(j, nd->nbEdges)
            if(edges[nd->edges[j]]->node1 == -1)
                nd->edges[j--] = nd->edges[--nd->nbEdges];
    }
}

void markShortestPath(int start, int arrival, int value)
{
    if(start == arrival)
        return;
    FOR(i, n)
    {
        if(i == arrival)
            continue;
        FOR(j, nodes[i]->nbEdges)
        {
            edge_t * e = edges[nodes[i]->edges[j]];
            if(e->node2 == arrival)
                if(nodes[arrival]->value - nodes[i]->value == e->value)
                {
                    e->node1 = -1;
                    markShortestPath(start, i, value - e->value);
                }
        }
    }
}

void dijkstra(int start)
{
	int * next = new int[n];
	int nbNext = 1;
	next[0] = start;
	while(nbNext > 0)
	{
		// get min dist from next
        int nextIdx = 0;
        node_t * node = nodes[next[nextIdx]];
		FOR3(1, i, nbNext)
			if(nodes[next[i]]->value < node->value)
			{
				node = nodes[next[i]];
				nextIdx = i;
			}
		// remove current node from next
		next[nextIdx] = next[--nbNext];
		FOR(i, node->nbEdges)
		{
            edge_t * e = edges[node->edges[i]];
            node_t * nextNode = nodes[e->node2];
            // stop if next node is already visited
            if(nextNode->visited)
                continue;
			// if new path is shorter than the previous...
			if(node->value + e->value < nextNode->value)
			{
				// ...set new dist
				nextNode->value = node->value + e->value;
				// add new node to next list
				if(!find(next, nbNext, e->node2))
					next[nbNext++] = e->node2;
			}
		}
		// tag node as visited
        node->visited = 1;
	}
	delete[] next;
}

/* Solve Almost Shortest Path
** https://icpcarchive.ecs.baylor.edu/external/42/4210.pdf
*/
int main(void)
{
    while(1)
    {
        // input
        cin >> n >> m;
        if(n == 0)
            return 0;
        nodes = new node_t*[n];
        edges = new edge_t*[m];
        FOR(i, n)
        {
            nodes[i] = new node_t;
            nodes[i]->visited = 0;
        }
        FOR(i, m)
            edges[i] = new edge_t;
        int start, arrival;
        cin >> start >> arrival;
        FOR(i, m)
            cin >> edges[i]->node1 >> edges[i]->node2 >> edges[i]->value;
        // set node nbEdges
        FOR(i, n)
            nodes[i]->nbEdges = 0;
        FOR(i, m)
            nodes[edges[i]->node1]->nbEdges++;
        // set node edges
        FOR(i, n)
            nodes[i]->edges = new int[nodes[i]->nbEdges];
        FOR(i, n)
            nodes[i]->nbEdges = 0;
        FOR(i, m)
        {
            node_t * node = nodes[edges[i]->node1];
            node->edges[node->nbEdges++] = i;
        }
        // set node values
        FOR(i, n)
            nodes[i]->value = INT_MAX;
        nodes[start]->value = 0;
#ifdef DEBUG
        cout << "nbNodes: " << n << endl << "nbEdges: " << m << endl;
        cout << "start: " << start << ", arrival: " << arrival << endl;
        FOR(i, m)
            cout << "edge " << i << ": [" << edges[i]->node1 << "," << edges[i]->node2 << "] size: " << edges[i]->value << endl;
        FOR(i, n)
        {
            cout << "node " << i << ": value: " << nodes[i]->value << ", [";
            FOR(j, nodes[i]->nbEdges)
                cout << edges[nodes[i]->edges[j]]->node2 << ",";
            cout << "]" << endl;
        }
#endif
        // algorithm
        dijkstra(start);
        markShortestPath(start, arrival, nodes[arrival]->value);
        removeShortestPath();
        FOR(i, n)
        {
            nodes[i]->value = INT_MAX;
            nodes[i]->visited = 0;
        }
        nodes[start]->value = 0;
#ifdef DEBUG
        FOR(i, m)
            cout << "edge " << i << ": [" << edges[i]->node1 << "," << edges[i]->node2 << "] size: " << edges[i]->value << endl;
        FOR(i, n)
        {
            cout << "node " << i << ": value: " << nodes[i]->value << ", [";
            FOR(j, nodes[i]->nbEdges)
                cout << edges[nodes[i]->edges[j]]->node2 << ",";
            cout << "]" << endl;
        }
#endif
        dijkstra(start);
        cout << ((nodes[arrival]->value == INT_MAX) ? -1 : nodes[arrival]->value) << endl;
        // free
        FOR(i, n)
            delete[] nodes[i]->edges;
        FOR(i, n)
            delete nodes[i];
        FOR(i, m)
            delete edges[i];
        delete[] nodes;
        delete[] edges;
    }
    return 0;
}
