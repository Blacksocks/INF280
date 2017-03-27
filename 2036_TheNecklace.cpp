#include <iostream>
#include <string.h>
#include <list>
#include <map>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1

using namespace std;

typedef struct edge_s
{
    int node1; // start node
    int node2; // node pointed
    int visited; // edge already visited?
} edge_t;

int m; // number of beads
map<int, list<int>> nmap;
edge_t ** edges;

void getNodesMap()
{
    map<int, list<int>>::iterator it;
    FOR(i, m)
    {
        if(edges[i]->node1 == edges[i]->node2)
            continue;
        nmap[edges[i]->node1].push_back(edges[i]->node2);
        nmap[edges[i]->node2].push_back(edges[i]->node1);
    }
}

/* return number of odds
 */
int getOdd(int * odd)
{
    int nbOdds = 0;
    for(map<int, list<int>>::iterator it = nmap.begin(); it != nmap.end(); ++it)
    {
        if(it->second.size() < 2)
            return -1;
        if(it->second.size() % 2 == 1)
        {
            if(nbOdds > 2)
                return 3;
            else if(nbOdds++ == 0)
                *odd = it->first;
        }
    }
    return nbOdds;
}

/* Find a loop in graph using backtracking algorithm
 */
void loopBacktracking(list<int> loop, int start)
{
    loop.push_back(start);
}

/* Solve The Necklace
** https://icpcarchive.ecs.baylor.edu/external/20/2036.pdf
*/
int main(void)
{
    int nbTests;
    cin >> nbTests;
    FOR(t, nbTests)
    {
        nmap.clear();
        // input
        cin >> m;
        edges = new edge_t*[m];
        FOR(i, m)
            edges[i] = new edge_t;
        FOR(i, m)
        {
            cin >> edges[i]->node1;
            cin >> edges[i]->node2;
            edges[i]->visited = 0;
        }
        getNodesMap();
#ifdef DEBUG
        cout << "nbRings: " << m << endl;
        FOR(i, m)
            cout << "[" << edges[i]->node1 << "," << edges[i]->node2 << "]" << endl;
        for(map<int, list<int>>::iterator it=nmap.begin(); it != nmap.end(); ++it)
        {
            cout << it->first << " => [";
            list<int>::const_iterator it2;
            for (it2 = it->second.begin(); it2 != it->second.end(); ++it2)
                std::cout << *it2 << ",";
            cout << "]\n";
        }
#endif
        // algorithm
        int odd = 0;
        int nbOdds = getOdd(&odd);
        cout << "Case #" << t << endl;
        if(nbOdds != 0 && nbOdds != 2)
            cout << "some beads may be lost" << endl;
        else
        {
            list<int> loop;
            loopBacktracking(loop, odd);
            cout << "Don't forget to link [x,x] edges at the end !" << endl;
        }
        cout << endl;
        // free
        FOR(i, m)
            delete edges[i];
        delete[] edges;
    }
    return 0;
}
