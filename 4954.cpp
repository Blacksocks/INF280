#include <iostream>

#define WIDTH           100
#define HEIGHT          75

#define FOR(i,n)        for(int i = 0; i < n; i++)

using namespace std;

// width of the cut
float w;

/* check if the whole segment is mowed
** we start at position 0 and try to find the next position to ovrelaps previous mowed
** maximum complexity: O(n2)
** x:                   array of positions
** n:                   size of positions array
** max:                 size of the segment
*/
int wholeMowed(float * x, int n, float max)
{
    float w2 = w / 2;
    float pos = -w2;
    float maxNextPos;
    int jump;
    int complete = 0;
    FOR(i, n)
    {
        jump = 0;
        maxNextPos = pos + w;
        FOR(j, n)
            if(x[j] > pos && x[j] <= maxNextPos)
            {
                pos = x[j];
                jump = 1;
                break;
            }
        if(!jump)
            break;
        if(pos + w2 >= max)
        {
            complete = 1;
            break;
        }
    }
    return complete;
}

/* Solve Lawn mower problem
** https://icpcarchive.ecs.baylor.edu/external/49/4954.pdf
*/
int main(void)
{
    int nx;
    int ny;
    scanf("%d", &nx);
    while(nx != 0)
    {
        // get inputs
        scanf("%d", &ny);
        scanf("%f", &w);
        float * x = new float[nx];
        float * y = new float[ny];
        FOR(i, nx)
            scanf("%f", x+i);
        FOR(i, ny)
            scanf("%f", y+i);

        if(wholeMowed(x, nx, HEIGHT) && wholeMowed(y, ny, WIDTH))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;

        // clear
        delete[] x;
        delete[] y;

        scanf("%d", &nx);
    }
    return 0;
}
