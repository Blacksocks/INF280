#include <iostream>
#include <string.h>
#include <list>
#include <climits>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1

using namespace std;

int W, H, w, h;
int ** PAINTING, painting;

inline int getPAINTING(int x, int y)
{
	return PAINTING[y * W + x];
}

inline void setPAINTING(int x, int y, int value)
{
	PAINTING[y * W + x] = value;
}

inline int getPainting(int x, int y)
{
	return painting[y * W + x];
}

inline void setPainting(int x, int y, int value)
{
	painting[y * W + x] = value;
}

/* Solve The Big Painting
** https://icpcarchive.ecs.baylor.edu/external/68/6893.pdf
*/
int main(void)
{
    char c;
    while(1)
    {
        // input
        if(!(cin >> w >> h >> W >> H))
            return 0;
        painting = new int[w * h];
        PAINTING = new int[W * H];
        FOR(i, h)
            FOR(j, w)
            {
                cin << c;
                setPainting(j, i, c);
            }
#ifdef DEBUG

#endif

    }
    return 0;
}
