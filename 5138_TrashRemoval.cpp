#include <iostream>
#include <string.h>
#include <list>
#include <cfloat>
#include <math.h>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1

using namespace std;

struct point {
    int x, y;
    double slope;
    point(): x(0), y(0) {slope = 0;}
    point(int in_x, int in_y): x(in_x), y(in_y) {slope = 0;}
    bool operator == (point pt) const {return (x == pt.x && y == pt.y);}
};

struct by_slope {
    bool operator()(point const &a, point const &b) {
        return a.slope < b.slope;
    }
};

double absolute(double x)
{
    return(x >= 0 ? x : -x);
}

double vect(point p1, point p2, point p3)
{
    int u1x = p2.x - p1.x;
    int u1y = p2.y - p1.y;
    int u2x = p3.x - p2.x;
    int u2y = p3.y - p2.y;
    return (u1x * u2y - u1y * u2x) * 1.0;
}

/* p1 and p2 form a line and this function return the distance between the line and p3
*/
double getDist(point p1, point p2, point p3)
{
    printf("[%d,%d] [%d,%d] [%d,%d]\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    // ax + by + c = 0
    double a, b, c;
    if(p2.x != p1.x)
    {
        a = (p2.y - p1.y) * 1.0 / (p2.x - p1.x);
        b = -1;
        c = p1.y - a * p1.x;
    }
    else
    {
        a = 0;
        b = 1;
        c = p1.x;
    }
    double res = absolute(a * p3.x + b * p3.y + c) / sqrt(a * a + b * b);
    printf("a, b, c: %lf, %lf, %f\n", a, b, c);
    printf("res: %lf\n", res);
    return res;
}

/* Get convex Polygon using Graham algorithm
** https://a3nm.net/work/teaching/2016-2017/inf280/6/GeomAlgo.pdf
*/
list<point> getConvex(list<point> points)
{
    // get orderded points
    point minXpoint = points.front();
    for(list<point>::iterator it = points.begin(); it != points.end(); it++)
        if((*it).x < minXpoint.x)
            minXpoint = *it;
    points.remove(minXpoint);
    for(list<point>::iterator it = points.begin(); it != points.end(); it++)
    {
        int xdiff = (*it).x - minXpoint.x;
        (*it).slope = xdiff == 0 ? ((*it).y > minXpoint.y ? DBL_MAX : DBL_MIN) : ((*it).y - minXpoint.y) * 1.0 / xdiff;
    }
    points.sort(by_slope());
    points.push_front(minXpoint);
#ifdef DEBUG
    printf("ordered\n");
    for(list<point>::iterator it = points.begin(); it != points.end(); it++)
        printf("[%d,%d] (%lf)\n", (*it).x, (*it).y, (*it).slope);
#endif
    // remove useless points
    list<point> result;
    result.push_back(points.front());
    points.pop_front();
    result.push_back(points.front());
    points.pop_front();
    for(list<point>::iterator it = points.begin(); it != points.end(); it++)
    {
        while(vect(*(prev(prev(result.end()))), result.back(), *it) < 0)
            result.pop_back();
        result.push_back(*it);
    }
    return result;
}

/* Solve Trash Removal
** https://icpcarchive.ecs.baylor.edu/external/51/5138.pdf
*/
int main(void)
{
    int n;
    int idx = 1;
    list<point> points;
    while(1)
    {
        // get input
        cin >> n;
        if(n == 0)
            return 0;
        FOR(i, n)
        {
            points.push_back(point());
            cin >> points.back().x >> points.back().y;
        }
#ifdef DEBUG
        printf("===== %d =====\n", n);
        int i = 0;
        for(list<point>::iterator it = points.begin(); it != points.end(); it++)
        {
            i++;
            printf("%d [%d,%d]\n", i, it->x, it->y);
        }
#endif
        // algorithm
        points = getConvex(points);
#ifdef DEBUG
        printf("convex\n");
        for(list<point>::iterator it = points.begin(); it != points.end(); it++)
            printf("[%d,%d]\n", (*it).x, (*it).y);
#endif
        double global_min_size = DBL_MAX;
        for(list<point>::iterator it = points.begin(); it != points.end(); it++)
        {
            if(it == points.begin())
                continue;
            double max_size = 0;
            for(list<point>::iterator it2 = it; it2 != points.end(); it2++)
            {
                if(it2 == it)
                    continue;
                double tmp_max_size = getDist(*prev(it), *it, *it2);
                printf("tmp_min_size: %lf / min_size: %lf\n", tmp_max_size, max_size);
                if(tmp_max_size > max_size)
                    max_size = tmp_max_size;
                else
                    break;
            }
            //
            printf("add\n");
            double tmp_max_size = getDist(points.back(), *prev(prev(points.end())), points.front());
            printf("tmp_min_size: %lf / min_size: %lf\n", tmp_max_size, max_size);
            if(tmp_max_size > max_size)
                max_size = tmp_max_size;
            tmp_max_size = getDist(points.back(), points.front(), *prev(prev(points.end())));
            printf("tmp_min_size: %lf / min_size: %lf\n", tmp_max_size, max_size);
            if(tmp_max_size > max_size)
                max_size = tmp_max_size;
            //
            printf("min_size: %lf / global_min_size: %lf\n\n", max_size, global_min_size);
            if(max_size < global_min_size)
                global_min_size = max_size;
        }
        cout << "Case " << idx++ << ": " << global_min_size << endl;

        // remove data
        points.clear();
    }
    return 0;
}
