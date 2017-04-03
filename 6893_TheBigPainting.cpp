#include <iostream>
#include <string.h>
#include <list>
#include <climits>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1

using namespace std;

int WIDTH, HEIGHT, width, height;
int * PAINTING;
int * painting;

inline int getPAINTING(int x, int y)
{
	return PAINTING[y * WIDTH + x];
}

inline void setPAINTING(int x, int y, int value)
{
	PAINTING[y * WIDTH + x] = value;
}

inline int getPainting(int x, int y)
{
	return painting[y * width + x];
}

inline void setPainting(int x, int y, int value)
{
	painting[y * width + x] = value;
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
        if(!(cin >> width >> height >> WIDTH >> HEIGHT))
            return 0;
        painting = new int[width * height];
        PAINTING = new int[WIDTH * HEIGHT];
        FOR(i, height)
            FOR(j, width)
            {
                cin >> c;
                setPainting(j, i, c == 'x');
            }
		FOR(i, HEIGHT)
            FOR(j, WIDTH)
            {
                cin >> c;
                setPAINTING(j, i, c == 'x');
            }
#ifdef DEBUG
	FOR(i, height)
	{
		FOR(j, width)
			cout << (getPainting(j, i) ? 'x' : 'o');
		cout << endl;
	}
	FOR(i, HEIGHT)
	{
		FOR(j, WIDTH)
			cout << (getPAINTING(j, i) ? 'x' : 'o');
		cout << endl;
	}
	cout << endl;
#endif
		delete[] painting;
		delete[] PAINTING;
    }
    return 0;
}
