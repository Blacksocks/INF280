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
    scanf("%d", &n);
    while(n != 0)
    {
        cout << "Case " << count << ":" << endl;
        // get inputs
        scanf("%d", &c);
        list<int> l;
        FOR(i, c)
            l.push_back(i+1);

        // for each order
        FOR(i, c)
        {
            scanf(" %c", &o);
            if(o == 'N')
            {
                int tmp = l.front();
                cout << tmp << endl;
                l.pop_front();
                l.push_back(tmp);
            }
            else
            {
                scanf("%d", &p);
                int tmp = 0;
                /*for (int n : l) {
                    std::cout << n << '\n';
                }*/
                for (list<int>::const_iterator it = l.begin(); it != l.end(); ++it)
                {
                    if(*it == p)
                    {
                        tmp = *it;
                        l.erase(it);
                        break;
                    }
                }
                l.push_back(tmp);
                cout << "TEST" << tmp << endl;
            }
        }

        scanf("%d", &n);
    }
    return 0;
}
