#include <iostream>
#include <string.h>
#include <list>
#include <climits>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1

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

int knuth_morris_pratt()
{
	int * dist = new int[WIDTH * HEIGHT + 1];
	int np = width;
	dist[0] = -1;
	int cnd = 0;
	for (int i = 1; i <= np; i++)
	{
		dist[i] = cnd;
		while (cnd >= 0 && painting[cnd] != painting[i])
			cnd = dist[cnd];
		cnd++;
	}

	int count = 0;
	int ns = WIDTH * HEIGHT;
	np = width;
	cnd = 0;
	for (int i = 0; i <= ns; i++)
	{
		while (cnd >= 0 && painting[cnd] != PAINTING[i])
			cnd = dist[cnd];
		cnd++;
		if (cnd == np)
		{
			int idx = i - np + 1;
			int x = idx % WIDTH;
			int y = idx / WIDTH;
			if(x + width > WIDTH)
				goto stop;
			if(y + height > HEIGHT)
				break;
			FOR3(1, k, height)
				FOR(l, width)
					if(getPainting(l, k) != getPAINTING(x + l, y + k))
						goto stop;
#ifdef DEBUG
			printf("idx:%d, x:%d, y:%d\n", idx, x, y);
#endif
			count++;
			stop:
			cnd = dist[cnd];
		}
	}
	delete[] dist;
	return count;
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
        if(!(cin >> height >> width >> HEIGHT >> WIDTH))
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
		/*FOR(i, height)
		{
			FOR(j, width)
				cout << (getPainting(j, i) ? 'x' : 'o');
			cout << endl;
		}*/
		/*FOR(i, HEIGHT)
		{
			FOR(j, WIDTH)
				cout << (getPAINTING(j, i) ? 'x' : 'o');
			cout << endl;
		}*/
		//cout << endl;
#endif
		cout << knuth_morris_pratt() << endl;
		delete[] painting;
		delete[] PAINTING;
    }
    return 0;
}
