#include <iostream>
#include <list>

#define FOR(i,n)        for(int i = 0; i < n; i++)

using namespace std;

/* Solve That is Your Queue problem
** https://icpcarchive.ecs.baylor.edu/external/44/4493.pdf
*/
int main(void)
{
    int n; // number of person
    int c; // number of commands
    char o; // order
    int p; // person to move in case of 'E' order
    int count = 1;
    int input = scanf("%d", &n);
	if(!input)
	{
		cout << "[ERROR] Reading input error." << endl;
		return 1;
	}
    while(n != 0)
    {
		cout << "Case " << count++ << ":" << endl;
        // get inputs
        input = scanf("%d", &c);
		if(!input)
		{
			cout << "[ERROR] Reading input error." << endl;
			return 1;
		}
		list<int> l;
        FOR(i, n)
            l.push_back(i+1);

        // for each order
        FOR(i, c)
        {
			input = scanf(" %c", &o);
			if(!input)
			{
				cout << "[ERROR] Reading input error." << endl;
				return 1;
			}
            if(o == 'N')
            {
                int tmp = l.front();
                cout << tmp << endl;
                l.pop_front();
                l.push_back(tmp);
            }
            else
            {
                input = scanf("%d", &p);
				if(!input)
				{
					cout << "[ERROR] Reading input error." << endl;
					return 1;
				}
                int tmp = 0;
				for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
                {
                    if(*it == p)
                    {
                        tmp = *it;
						l.erase(it);
                        break;
                    }
                }
                l.push_front(tmp);
            }
        }
        input = scanf("%d", &n);
		if(!input)
		{
			cout << "[ERROR] Reading input error." << endl;
			return 1;
		}
    }
    return 0;
}
