#include <iostream>
#include <string.h>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1

using namespace std;

int * rings;

/* return the value of a ring
 * idx must be between 0 and 1
 */
inline int getRing(int ring, int idx)
{
    return rings[2 * ring + idx];
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
        // input
        int n; // number of beads
        cin >> n;
        rings = new int[2 * n];
        FOR(i, 2 * n)
            cin >> rings[i];
#ifdef DEBUG
        cout << "nbRings: " << n << endl;
        FOR(i, n)
            cout << "[" << getRing(i, 0) << "," << getRing(i, 1) << "]" << endl;
#endif
        // algorithm

        // free
        delete[] rings;
    }
    return 0;
}
