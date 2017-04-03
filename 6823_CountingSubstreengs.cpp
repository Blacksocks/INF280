#include <iostream>
#include <string.h>
#include <list>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1

using namespace std;

char c;

inline int isNumber(char c)
{
    return (c >= '0' && c <= '9');
}

inline int is3Multiple(char c)
{
    return (c == '0' || c == '3' || c == '6' || c == '9');
}

void shift(long int * nbMultiples, int n)
{
    if(n == 1)
    {
        int tmp = nbMultiples[0];
        nbMultiples[0] = nbMultiples[2];
        nbMultiples[2] = nbMultiples[1];
        nbMultiples[1] = tmp;
    }
    else if(n == 2)
    {
        int tmp = nbMultiples[0];
        nbMultiples[0] = nbMultiples[1];
        nbMultiples[1] = nbMultiples[2];
        nbMultiples[2] = tmp;
    }
}

/* Solve Counting substhreengs
** https://icpcarchive.ecs.baylor.edu/external/68/6823.pdf
*/
int main(void)
{
    char c = 0;
    long int nbMultiples[3] = {0, 0, 0}; // nombres de nombres tel que x%3 = 0, 1, 2
    int sum = 0;
    long int result = 0;
    while(1)
    {
        if((c = getchar()) == EOF)
            return 0;
        if(isNumber(c))
        {
            int val = (c - '0') % 3;
            shift(nbMultiples, val);
            sum += val;
            result += nbMultiples[0];
            nbMultiples[val % 3]++;
            if(is3Multiple(c))
                result++;
        }
        else if(c == '\n')
        {
            cout << result << endl;
            FOR(i, 3)
                nbMultiples[i] = 0;
            sum = 0;
            result = 0;
        }
        else
        {
            sum = 0;
            FOR(i, 3)
                nbMultiples[i] = 0;
        }
#ifdef DEBUG
        cout << "nbMultiples: [" << nbMultiples[0] << "," << nbMultiples[1] << "," << nbMultiples[2] << "], sum: " << sum << ", result: " << result << endl;
#endif
    }
    return 0;
}
