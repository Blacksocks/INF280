#include <iostream>
#include <string.h>
#include <list>
#include <math.h>

#define FOR(i,n)        for(int i = 0; i < n; i++)
#define FOR3(m,i,n)     for(int i = m; i < n; i++)

#define DEBUG			1

#define EPSILON         0.01

typedef struct point_s {
    double x;
    double y;
} point_t;

using namespace std;

void copy(point_t * p1, point_t p2)
{
    p1->x = p2.x;
    p1->y = p2.y;
}

double absolute(double x)
{
    return (x >= 0) ? x : -x;
}

/* Calcul du centre du cercle circonscrit à partir de trois points
** http://stackoverflow.com/questions/4103405/what-is-the-algorithm-for-finding-the-center-of-a-circle-from-three-points
*/
point_t circleCenter(point_t p1, point_t p2, point_t p3)
{
    point_t center;
    double aSlope = (p2.y - p1.y) / (p2.x - p1.x);
    double bSlope = (p3.y - p2.y) / (p3.x - p2.x);
    center.x = (aSlope * bSlope * (p1.y - p3.y) + bSlope * (p1.x + p2.x) - aSlope * (p2.x + p3.x)) / (2 * (bSlope - aSlope));
    center.y = -1 * (center.x - (p1.x + p2.x) / 2) / aSlope + (p1.y + p2.y) / 2;
    return center;
}

/* Calcul d'un angle entre 3 points, le premier étant le centre
** http://stackoverflow.com/questions/1211212/how-to-calculate-an-angle-from-three-points
*/
inline double getAngle(point_t p1, point_t p2, point_t p3)
{
    double a21 = atan2(p2.y - p1.y, p2.x - p1.x);
    double a31 = atan2(p3.y - p1.y, p3.x - p1.x);
    while(a21 < 0)
        a21 += 2 * M_PI;
    while(a31 < 0)
        a31 += 2 * M_PI;
    printf("[%lf, %lf]\n", a21*180/M_PI, a31*180/M_PI);
    return(a21 - a31);
}

int isDividing(double a, double angle)
{
    double division = a / angle;
    if(division - (int)division < EPSILON)
        return (int)division;
    return 0;
}

/* Solve Regular Convex Polygon
** https://icpcarchive.ecs.baylor.edu/external/58/5827.pdf
*/
int main(void)
{
    point_t p1;
    point_t p2;
    point_t p3;
    while(1)
    {
        if(!(cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y))
            return 0;

        // get center point
        point_t c = circleCenter(p1, p2, p3);

        // get angles and set the minimum in a1
        double a1, a2, a3;
        a1 = getAngle(c, p1, p2);
        /*if(a1 > M_PI)
            a1 = 2 * M_PI - a1;*/
        a2 = getAngle(c, p2, p3);
        /*if(a2 > M_PI)
            a2 = 2 * M_PI - a2;*/
        a3 = getAngle(c, p3, p1);
        int nb_neg = (a1 < 0) + (a2 < 0) + (a3 < 0);
        if((a1 < 0) + (a2 < 0) + (a3 < 0) == 1)
        {
            if(a1 < 0)
                a1 = 2 * M_PI + a1;
            if(a2 < 0)
                a2 = 2 * M_PI + a2;
            if(a3 < 0)
                a3 = 2 * M_PI + a3;
        }
        else
        {
            if(a1 > 0)
            {
                a1 = 2 * M_PI - a1;
                // ax = abs(ax)
            }
            // faire la mm pour a2 et a3
            if(a2 > 0)
                a2 = 2 * M_PI - a2;
            if(a3 > 0)
                a3 = 2 * M_PI - a3;
        }
        printf("==============================\n");
        printf("center: [%lf, %lf]\n", c.x, c.y);
        printf("sum angles: %lf\n", (a1+a2+a3)*180/M_PI);
        printf("a1:%lf, a2:%lf, a3:%lf\n", a1*180/M_PI, a2*180/M_PI, a3*180/M_PI);
        continue;
        int i = 0;
        while(i <= 1000)
        {
            double angle = a1 / i;
            int nb2 = isDividing(a2, angle);
            int nb3 = isDividing(a3, angle);
            if(nb2 + nb3 + i == 491)
            {
                printf("div2:%lf, div3:%lf\n", a2 / angle, a3 / angle);
                printf("i:%d, angle:%lf, nb2:%d, nb3:%d\n", i, angle, nb2, nb3);
            }
            if(nb2 && nb3)
            {
                cout << (nb2 + nb3 + i) << endl;
                break;
            }
            i++;
        }
        if(i == 1001)
        {
            cout << "ERROR Too small EPSILON" << endl;
            return 1;
        }
    }
    return 0;
}
