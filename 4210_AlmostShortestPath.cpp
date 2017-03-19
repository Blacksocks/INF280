#include <iostream>
#include <string.h>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1

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
} node_t;

int n; // number of nodes
int m; // number of edges
int start; // start index
int arrival; // arrival index
edge_t ** edges; // graph edges
node_t ** nodes; // graph nodes
int nbEdges; // number of edges
int nbNodes; // number of nodes

/* return 1 if the value is into the array, 0 else
*/
int find(int * array, int lenArray, int value)
{
    FOR(i, lenArray)
        if(array[i] == value)
            return 1;
    return 0;
}

int dijkstra()
{
	int * next = new int[nbNodes];
	int nbNext = 1;
	next[0] = 0;

	int COUNT = 0;

	while(nbNext > 0)
	{
		if(COUNT++ > 10000)
		{
			printf("MAX TIME EXCEDDED\n");
			return 0;
		}
		// get min dist from next
        int nextIdx = 0;
        node_t * node = nodes[next[nextIdx]];
		FOR3(1, i, nbNext)
			if(nodes[next[i]]->value < node->value)
			{
				node = nodes[next[i]];
				nextIdx = i;
			}
        int nodeIdx = next[nextIdx];
		if(nodeIdx == arrival)
			return 0;
		// remove current node from next
		next[nextIdx] = next[--nbNext];
		FOR(i, node->nbEdges)
		{
            edge_t * e = edges[i];
            node_t * nextNode = nodes[e->node2];
            // stop if next node is already visited
            if(nextNode->value == -1)
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
        node->value = -1;
	}
	delete[] next;
	return 0;
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
            nodes[i] = new node_t;
        FOR(i, m)
            edges[i] = new edge_t;
        cin >> start >> arrival;
        FOR(i, m)
            cin >> edges[i]->node1 >> edges[i]->node2 >> edges[i]->value;
#ifdef DEBUG
        cout << "nbNodes: " << n << endl << "nbEdges: " << m << endl;
        cout << "start: " << start << ", arrival: " << arrival << endl;
        FOR(i, m)
            cout << "edge " << i << ": [" << edges[i]->node1 << "," << edges[i]->node2 << "] size: " << edges[i]->value << endl;
#endif
        // algorithm

        // free
        FOR(i, n)
            delete nodes[i];
        FOR(i, m)
            delete edges[i];
        delete[] nodes;
        delete[] edges;
    }
    return 0;
}
