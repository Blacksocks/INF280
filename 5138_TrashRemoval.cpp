#include <iostream>
#include <string.h>
#include <list>
#include <cfloat>
#include <math.h>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

//#define DEBUG			1

#define MIN             (-FLT_MAX/2)
#define MAX             (FLT_MAX/2)

using namespace std;

struct point {
    int x, y;
    float slope;
    point(): x(0), y(0) {slope = 0;}
    point(int in_x, int in_y): x(in_x), y(in_y) {slope = 0;}
    bool operator == (point pt) const {return (x == pt.x && y == pt.y);}
};

struct by_slope {
    bool operator()(point const &a, point const &b) {
        return a.slope < b.slope;
    }
};

float absolute(float x)
{
    return(x >= 0 ? x : -x);
}

int vect(point p1, point p2, point p3)
{
    int u1x = p2.x - p1.x;
    int u1y = p2.y - p1.y;
    int u2x = p3.x - p2.x;
    int u2y = p3.y - p2.y;
    return (u1x * u2y - u1y * u2x);
}

/* p1 and p2 form a line and this function return the distance between the line and p3
*/
float getDist(point p1, point p2, point p3)
{
#ifdef DEBUG
    printf("[%d,%d] [%d,%d] [%d,%d]\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
#endif
    // ax + by + c = 0
    float a, b, c;
    if(p2.x != p1.x)
    {
        a = (p2.y - p1.y) * 1.0 / (p2.x - p1.x);
        b = -1;
        c = p1.y - a * p1.x;
    }
    else
    {
        a = -1;
        b = 0;
        c = p1.x;
    }
    float res = absolute(a * p3.x + b * p3.y + c) / sqrt(a * a + b * b);
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
        (*it).slope = (xdiff == 0 ? ((*it).y > minXpoint.y ? MAX : MIN) : ((*it).y - minXpoint.y) * 1.0 / xdiff);
    }
    points.sort(by_slope());
    points.push_front(minXpoint);
#ifdef DEBUG
    int i = 1;
    printf("ordered\n");
    for(list<point>::iterator it = points.begin(); it != points.end(); it++)
        printf("%d [%d,%d] (%lf)\n", i++, (*it).x, (*it).y, (*it).slope);
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
        if(vect(*(prev(prev(result.end()))), result.back(), *it) == 0)
        {
            result.pop_back();
            while(vect(*(prev(prev(result.end()))), result.back(), *it) < 0)
                result.pop_back();
        }
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
        int i = 1;
        for(list<point>::iterator it = points.begin(); it != points.end(); it++)
            printf("%d [%d,%d]\n", i++, it->x, it->y);
#endif
        // algorithm
        points = getConvex(points);
#ifdef DEBUG
        printf("convex\n");
        for(list<point>::iterator it = points.begin(); it != points.end(); it++)
            printf("[%d,%d]\n", (*it).x, (*it).y);
#endif
        float global_min_size = DBL_MAX;
        for(list<point>::iterator it = points.begin(); it != points.end(); it++)
        {
            /*if(it == points.begin())
                continue;*/
            float max_size = 0;
            for(list<point>::iterator it2 = next(it); it2 != it; it2++)
            {
                if(it2 == points.end())
                    it2 = points.begin();
                point it_1 = (it == points.begin() ? points.back() : *prev(it));
                float tmp_max_size = getDist(it_1, *it, *it2);
#ifdef DEBUG
                printf("tmp_max_size: %lf / max_size: %lf\n", tmp_max_size, max_size);
#endif
                if(tmp_max_size > max_size)
                    max_size = tmp_max_size;
                else
                    break;
            }
#ifdef DEBUG
            printf("min_size: %lf / global_min_size: %lf\n\n", max_size, global_min_size);
#endif
            if(max_size < global_min_size)
                global_min_size = max_size;
        }
        printf("Case %d: %.2lf\n", idx++, /*round(*/global_min_size/* * 100) / 100.0*/);

        // remove data
        points.clear();
    }
    return 0;
}
