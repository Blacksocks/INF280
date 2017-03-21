#include <iostream>
#include <string.h>
#include <climits>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1

using namespace std;

int * grid;
int * duration;
int * dist;
int n;

inline int idx(int x, int y)
{
	return y * n + x;
}

inline int get(int * array, int x, int y)
{
	return array[idx(x, y)];
}

inline void set(int * array, int x, int y, int value)
{
	array[idx(x, y)] = value;
}

inline int getX(int pos)
{
	return pos % n;
}

inline int getY(int pos)
{
	return pos / n;
}

int find(int * array, int len, int value)
{
	FOR(i, len)
		if(array[i] == value)
			return 1;
	return 0;
}

int isReachable(int t, int x, int y)
{
	int i = idx(x, y);
	if(duration[i] == 0)
		return grid[i];
	return (t % (2 * duration[i]) - duration[i] + 1) * (grid[i] ? 1 : -1) <= 0;
}

void printArray(int * array)
{
	FOR(j, n)
	{
		FOR(i, n)
		{
			if (get(array, i, j) == INT_MAX)
			{
				cout << "  ";
				continue;
			}
			if (get(array, i, j) < 10)
				cout << " ";
			cout << get(array, i, j);
		}
		cout << endl;
	}
}

int dijkstra()
{
	int * visited = new int[n *n];
	int nbVisited = 0;
	int * next = new int[n *n];
	int nbNext = 1;
	int * sleep = new int[n *n];
	FOR(j, n)
		FOR(i, n)
			set(sleep, i, j, 0);
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
		int minDistIdx = next[0];
		int nextIdx = 0;
		FOR3(1, i, nbNext)
			if(dist[next[i]] < dist[minDistIdx])
			{
				minDistIdx = next[i];
				nextIdx = i;
			}
		if(minDistIdx == idx(n - 1, n - 1))
			return 0;
		// in each direction
		int tmpX = getX(minDistIdx);
		int tmpY = getY(minDistIdx);
		int d = dist[minDistIdx] + 1;
		// remove current node from next
		if(!isReachable(d, tmpX, tmpY))
		{
			sleep[minDistIdx] = 0;
			next[nextIdx] = next[--nbNext];
		}
		else
		{
			dist[minDistIdx] = d;
			sleep[minDistIdx]++;
		}
		FOR(i, 4)
		{
			tmpX = getX(minDistIdx);
			tmpY = getY(minDistIdx);
			switch(i)
			{
				case 0: tmpY--; break;
				case 1: tmpY++; break;
				case 2: tmpX++; break;
				case 3: tmpX--; break;
			}
			// if node position out of range, pass
			if(tmpX < 0 || tmpY < 0 || tmpX == n || tmpY == n)
				continue;
			// if the node is not reachable, pass
			if(!isReachable(d, tmpX, tmpY))
				continue;
			// if new path is shorter than the previous...
			if(get(dist, tmpX, tmpY) > d)
			{
				// ...set new dist
				set(dist, tmpX, tmpY, d);
				// add new node to next list
				if(!find(next, nbNext, idx(tmpX, tmpY)))
					next[nbNext++] = idx(tmpX, tmpY);
			}
		}
		// add visited node
		visited[nbVisited++] = minDistIdx;
	}
	delete[] visited;
	delete[] next;
	return 0;
}

/* Solve Men at Work
** https://icpcarchive.ecs.baylor.edu/external/29/2939.pdf
*/
int main(void)
{
	while(cin >> n)
	{
		// get grid
		grid = new int[n * n];
		char c;
		FOR(j, n)
			FOR(i, n)
			{
				cin >> c;
				set(grid, i, j, c == '*' ? 0 : 1);
			}
		// get durations
		duration = new int[n * n];
		FOR(j, n)
			FOR(i, n)
			{
				cin >> c;
				set(duration, i, j, c - '0');
			}
		// init dist to INT_MAX
		dist = new int[n * n];
		FOR(j, n)
			FOR(i, n)
				set(dist, i, j, INT_MAX);
		// set rrot dist to 0
		set(dist, 0, 0, 0);
#ifdef DEBUG
		printf("N: %d\n\nGrid:\n", n);
		printArray(grid);
		cout << "Duration:"  << endl;
		printArray(duration);
		cout << endl;
#endif
		dijkstra();
#ifdef DEBUG
		cout << "Distances:"  << endl;
		printArray(dist);
		cout << endl;
#endif
		// clean
		delete[] grid;
		delete[] duration;
		delete[] dist;
	}
    return 0;
}
