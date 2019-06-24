#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>


// clang-format off
#ifndef LOAD_TEST
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DO_LOAD_TEST(N) do {} while (false)
#else
#include "../load_test.hpp"
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DO_LOAD_TEST(N) auto re_ref = load_test(__FILE__, (N))
#endif
// clang-format on

using namespace std;

using ll = long long;
using ull = unsigned long long;
using sz = size_t;

using pll = pair<ll, ll>;
using vpll = vector<pll>;
using vvpll = vector<vpll>;

using vl = vector<ll>;
using vvl = vector<vl>;

using sl = set<ll>;
using vsl = vector<sl>;


#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

double DEG_to_RAD(double d) {
    return d * PI / 180.0;
}

double RAD_to_DEG(double r) {
    return r * 180.0 / PI;
}


struct point {
    double x, y; // only used if more precision is needed
    point() {
        x = y = 0.0;
    } // default constructor
    point(double _x, double _y) : x(_x), y(_y) {
    }
    point operator+(const point& p) const {
        return {x + p.x, y + p.y};
    }
    point operator-(const point& p) const {
        return {x - p.x, y - p.y};
    }
    bool operator<(point other) const { // override less than operator
        if (fabs(x - other.x) > EPS)    // useful for sorting
            return x < other.x;         // first criteria , by x-coordinate
        return y < other.y;
    } // second criteria, by y-coordinate
    // use EPS (1e-9) when testing equality of two floating points
    bool operator==(point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
};

double dist(point p1, point p2) { // Euclidean distance
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(p1.x - p2.x, p1.y - p2.y);
} // return double

// rotate p by theta radians CCW w.r.t origin (0, 0)
point rotate(point p, double rad) {
    return point(p.x * cos(rad) - p.y * sin(rad), p.x * sin(rad) + p.y * cos(rad));
}


struct vec {
    double x, y; // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {
    }
};

vec toVec(point a, point b) { // convert 2 points to vector a->b
    return vec(b.x - a.x, b.y - a.y);
}

vec scale(vec v, double s) { // nonnegative s = [<1 .. 1 .. >1]
    return vec(v.x * s, v.y * s);
} // shorter.same.longer

point translate(point p, vec v) { // translate p according to v
    return point(p.x + v.x, p.y + v.y);
}

double dot(vec a, vec b) {
    return (a.x * b.x + a.y * b.y);
}

double norm_sq(vec v) {
    return v.x * v.x + v.y * v.y;
}

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b) {
    // formula: c = a + u * ab
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    point c = translate(a, scale(ab, u)); // translate a to c
    return dist(p, c);
} // Euclidean distance between p and c

double angle(point a, point o, point b) { // returns angle aob in rad
    vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

double cross(vec a, vec b) {
    return a.x * b.y - a.y * b.x;
}

double cross(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r));
}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > 0;
}


vector<point> convex_hull(vector<point> Points) {
    //-------------- incremental alg. ---------
    // upper hull
    sort(Points.begin(), Points.end());
    stack<point> stk_up;
    stk_up.push(Points[0]);
    stk_up.push(Points[1]);
    for (ull i = 2; i < Points.size(); i++) {
        while ((stk_up.size() >= 2)) {
            point p2, p3;
            p2 = stk_up.top();
            stk_up.pop();
            p3 = stk_up.top();
            // cross(ch[m-2], ch[m-1], p[i]) <= 0
            // ccw(p[i], ch[m-1], ch[m-2])
            if (ccw(Points[i], p2, p3)) {
                stk_up.push(p2);
                break;
            }
        }
        stk_up.push(Points[i]);
    }
    // lower hull
    for (ull i = 0; i < Points.size(); i++) {
        Points[i].x = -Points[i].x;
        Points[i].y = -Points[i].y;
    }
    sort(Points.begin(), Points.end());
    stack<point> stk_low;
    stk_low.push(Points[0]);
    stk_low.push(Points[1]);
    for (ull i = 2; i < Points.size(); i++) {
        while ((stk_low.size() >= 2)) {
            point p2, p3;
            p2 = stk_low.top();
            stk_low.pop();
            p3 = stk_low.top();
            if (ccw(Points[i], p2, p3)) {
                stk_low.push(p2);
                break;
            }
        }
        stk_low.push(Points[i]);
    }

    // print convex hull - cw order from leftmost point
    vector<point> CH;
    stk_low.pop();
    point p;
    while (!stk_low.empty()) {
        p = stk_low.top();
        p.x = -p.x;
        p.y = -p.y;
        CH.push_back(p);
        stk_low.pop();
    }
    stk_up.pop();
    while (!stk_up.empty()) {
        CH.push_back(stk_up.top());
        stk_up.pop();
    }
    // reverse(CH.begin(), CH.end()); // ccw -> cw
    return CH;
}


double minimum_width(vector<point>& pt) {
    ull n = pt.size();

    if (n <= 2)
        return 0.0;

    double ret = INF;

    ull i = 0, j = 0;
    while (i < n) {
        while (cross(pt[i], pt[(i + 1) % n], pt[(j + 1) % n]) >= cross(pt[i], pt[(i + 1) % n], pt[j]))
            j = (j + 1) % n;
        double dist = distToLine(pt[j], pt[i], pt[(i + 1) % n]);
        ret = min(ret, dist);
        i++;
    }
    return ret;
}

/// 1111 - Trash Removal
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    DO_LOAD_TEST(1);

    ull n;
    ull tcn = 1;
    while (cin >> n) {
        if (n == 0) {
            break;
        }
        vector<point> ps;
        for (ull i = 0; i < n; ++i) {
            double x, y;
            cin >> x >> y;
            ps.emplace_back(x, y);
        }
        vector<point> ch = convex_hull(ps);
        double width = minimum_width(ch);
        cout << "Case " << tcn++ << ": " << setprecision(2) << fixed << (ceil(width * 100) / 100.0) << endl;
    }
}
