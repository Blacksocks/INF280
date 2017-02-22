#include <iostream>
#include <list>

#define FOR(i,n)        for(int i = 0; i < n; i++)

using namespace std;

inline void check_input(int input)
{
	if(!input)
	{
		cout << "[ERROR] Reading input error." << endl;
		exit(1);
	}
}

/* Solve That is Your Queue problem
** https://icpcarchive.ecs.baylor.edu/external/44/4493.pdf
*/
int main(void)
{
    int n = 1; // number of person
    int c; // number of commands
    char o; // order
    int count = 1;
    while(1)
    {
		check_input(scanf("%d %d", &n, &c));
		if(n == 0) return 0;
		printf("Case %d:\n", count++);
		list<int> l;
		if(c < n) n = c;
        FOR(i, n) l.push_back(i+1);
        // for each order
        FOR(i, c)
        {
			check_input(scanf("\n%c", &o));
            if(o == 'N')
            {
                printf("%d\n", l.front());
                l.push_back(l.front());
				l.pop_front();
            }
            else // 'E' order
            {
				int p; // person to move
                check_input(scanf("%d", &p));
				l.remove(p);
				l.push_front(p);
            }
        }
    }
    return 0;
}
