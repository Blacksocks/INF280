#include <iostream>
#include <string.h>
#include <list>
#include <climits>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1

using namespace std;

typedef struct edge_s
{
    int node1; // start node
    int node2; // node pointed
} edge_t;

typedef struct node_s
{
    int * edges; // linked edges index
    int nbEdges; // number of linked edges
} node_t;

int n; // number of nodes
int m; // number of edges
edge_t ** edges; // graph edges
node_t ** nodes; // graph nodes
list<int> treeConfig;
list<int> bestConfig;
list<uint32_t> monkeyPrevPos;
int nb_fire;

void update_values(uint32_t * monkeyNextPos, uint32_t monkeyCurrPos)
{
    uint32_t tmp = 1;
    FOR(i, n)
    {
        if(monkeyCurrPos & tmp)
            FOR(j, nodes[i]->nbEdges)
                *monkeyNextPos |= (uint32_t)1 << nodes[i]->edges[j];
        tmp  = tmp << 1;
    }
}

void fire(int treeIdx, uint32_t monkeyPos)
{
    // attention, ne prend pas en compte l'ordre lexicographique
    if((int)treeConfig.size() >= nb_fire)
        return;
    uint32_t monkeySavePos = monkeyPos & ~((uint32_t)1 << treeIdx);
    monkeyPos = 0;
    treeConfig.push_back(treeIdx);
    update_values(&monkeyPos, monkeySavePos);
    int stop = 0;
    for(std::list<uint32_t>::iterator it = monkeyPrevPos.begin(); it != monkeyPrevPos.end(); it++)
        if(monkeyPos == *it)
        {
            stop = 1;
            break;
        }
    monkeyPrevPos.push_back(monkeyPos);
    // this solution doesn't end
    if(stop);
    // aucune position n'est possible pour le monkey
    else if(monkeyPos == 0)
    {
        // attention, ne prend pas en compte l'ordre lexicographique
        if((int)treeConfig.size() < nb_fire)
        {
            nb_fire = (int)treeConfig.size();
            // copy treeConfig in bestConfig
            bestConfig.clear();
            for(std::list<int>::iterator it = treeConfig.begin(); it != treeConfig.end(); it++)
                bestConfig.push_back(*it);
        }
    }
    // toutes les positions sont envisageables pour la position du monkey
    else if(__builtin_popcount(monkeyPos) != n)
    {
        int nbMonkeySavePrevPos = monkeyPrevPos.size();
        uint32_t tmp = 1;
        FOR(i, n)
        {
            if(monkeyPos & tmp)
                fire(i, monkeyPos);
            tmp = tmp << 1;
        }
        while((int)monkeyPrevPos.size() > nbMonkeySavePrevPos)
            monkeyPrevPos.pop_back();
    }
    treeConfig.pop_back();
    // charging
    monkeyPos = monkeySavePos;
}

/* Solve Jumping Monkey
** https://icpcarchive.ecs.baylor.edu/external/20/2036.pdf
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
        FOR(i, m)
            cin >> edges[i]->node1 >> edges[i]->node2;
        // set node nbEdges
        FOR(i, n)
            nodes[i]->nbEdges = 0;
        FOR(i, m)
            nodes[edges[i]->node1]->nbEdges++;
        FOR(i, m)
            nodes[edges[i]->node2]->nbEdges++;
        // set node edges
        FOR(i, n)
            nodes[i]->edges = new int[nodes[i]->nbEdges];
        FOR(i, n)
            nodes[i]->nbEdges = 0;
        FOR(i, m)
        {
            node_t * node = nodes[edges[i]->node1];
            node->edges[node->nbEdges++] = edges[i]->node2;
            node = nodes[edges[i]->node2];
            node->edges[node->nbEdges++] = edges[i]->node1;
        }
#ifdef DEBUG
        cout << endl << "nbNodes: " << n << endl << "nbEdges: " << m << endl;
        FOR(i, m)
            cout << "edge " << i << ": [" << edges[i]->node1 << "," << edges[i]->node2 << "] size: " << endl;
        FOR(i, n)
        {
            cout << "node " << i << ": [";
            FOR(j, nodes[i]->nbEdges)
                cout << nodes[i]->edges[j] << ",";
            cout << "]" << endl;
        }
#endif
        // Brute force
        nb_fire = INT_MAX;
        monkeyPrevPos.clear();
        bestConfig.clear();
        FOR(i, n)
            fire(i,((int)1 << n) - 1);
        if((int)bestConfig.size() == 0)
        {
            cout << "Impossible" << endl;
            continue;
        }
        cout << bestConfig.size() << ":";
        for(std::list<int>::iterator it = bestConfig.begin(); it != bestConfig.end(); it++)
            cout << " " << *it;
        cout << endl;
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
