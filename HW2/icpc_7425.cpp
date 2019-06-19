#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <stack>

using namespace std;

using vi = vector<int>;
using vb = vector<bool>;
typedef vector<int> vi;
typedef vector<vi> vvi;


using namespace std;


typedef pair<int, int> Point;
typedef pair<Point, Point> Segment;

bool isInSegment(Point p, Point q, Point r)
{
    return q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) &&
           q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second);
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.second - p.second) * (r.first - q.first) -
              (q.first - p.first) * (r.second - q.second);

    if (val == 0) return 0;

    return (val > 0)? 1: 2;
}

// find if two segments are intersecting
bool doIntersect(Point p1, Point q1, Point p2, Point q2)
{
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    if (o1 != o2 && o3 != o4) {
        return true;
    }

    return (o1 == 0 && isInSegment(p1, p2, q1)) ||
           (o2 == 0 && isInSegment(p1, q2, q1)) ||
           (o3 == 0 && isInSegment(p2, p1, q2)) ||
           (o4 == 0 && isInSegment(p2, q1, q2));
}


bool dfs(vvi &intersections, vi& colors, int u, int c) {
    if (colors[u] != -1) {
        return colors[u] == c;
    }

    colors[u] = c;
    for (int v : intersections[u]) {
        if (!dfs(intersections, colors, v, 1-c))
            return false;
    }
    return true;
}

int main()
{
    int wells_n, pipes_n;
    while (cin >> wells_n >> pipes_n) {
        // Wells
        vector<int> wells_x, wells_y;
        vector<Point> wells;
        int x,y,w;
        for (int i=0 ; i<wells_n ; i++) {
            // wells are numbered 1...w
            cin >> x;
            cin >> y;
            wells.emplace_back(x,y);
        }
        // Pipes
        vector<Segment> pipes;

        for (int i=0 ; i<pipes_n ; i++) {
            // wells are numbered 1...w
            cin >> w;
            cin >> x;
            cin >> y;

            pipes.emplace_back(wells[w-1], make_pair(x,y));
        }
        // find intersections
        vvi intersections(pipes_n);
        for (int i = 0; i < pipes_n; ++i) {
            for (int j = i + 1; j < pipes_n; ++j) {
                if (pipes[i].first != pipes[j].first) {
                    if (doIntersect(pipes[i].first, pipes[i].second,
                                          pipes[j].first, pipes[j].second)) {
                        intersections[i].emplace_back(j);
                        intersections[j].emplace_back(i);
                    }
                }
            }
        }

        // solve the problem as graph 2-coloring problem
        vi colors(pipes_n, -1);
        int color = 1;
        int res = true;
        for (int i = 0; i < pipes_n; ++i) {
            if (colors[i] == -1)
                res = res && dfs(intersections, colors, i, color);
        }
        cout << (res? "possible":"impossible") << endl;

    }

    return 0;
}