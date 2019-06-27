#define _USE_MATH_DEFINES
#include <algorithm>
#include <cmath>
#include <stack>
#include <vector>

using ll = long long;
using ull = unsigned long long;

using namespace std;

static constexpr double EPS = 1e-9;
static constexpr double INF = 1e9;

double DEG_to_RAD(double d) {
    return d * M_PI / 180.0;
}
double RAD_to_DEG(double r) {
    return r * 180.0 / M_PI;
}

/// type of points can be chosen here, but some modification are also needed in some functions.
using pt_type = double;
// using pt_type = ll;
struct pt {
    pt_type x, y;

    pt() = default;

    pt(pt_type _x, pt_type _y) : x(_x), y(_y) {
    }
    pt operator+(const pt& p) const {
        return {x + p.x, y + p.y};
    }

    pt operator-(const pt& p) const {
        return {x - p.x, y - p.y};
    }

    pt operator-() const {
        return {-x, -y};
    }

    pt_type cross(const pt& p) const {
        return x * p.y - y * p.x;
    }

    pt_type dot(const pt& p) const {
        return x * p.x + y * p.y;
    }

    pt_type cross(const pt& a, const pt& b) const { // cross of a and b
        return (a - *this).cross(b - *this);        // with this point as the origin
    }

    pt_type dot(const pt& a, const pt& b) const { // dot of a and b
        return (a - *this).dot(b - *this);        // with this point as the origin
    }

    pt_type len_sqr() const { // X^2 + Y^2 without taking the root
        return this->dot(*this);
    }

    // *** start of code for near precision compares ***
    bool operator<(const pt& p) const { // lexicographical smaller than
        if (fabs(x - p.x) > EPS)        // useful for sorting
            return x < p.x;             // first criteria , by x-coordinate
        return y < p.y;                 // second criteria, by y-coordinate
    }

    // use EPS (1e-9) when testing equality of two floating points
    bool operator==(const pt& p) const {
        return (fabs(x - p.x) < EPS) and (fabs(y - p.y) < EPS);
    }
    // *** end of code for near precision compares *** */

    /* // *** start of code for exact compares ***
    bool operator<(const pt& p) const {           // lexicographical smaller than
        return x < p.x or (x == p.x and y < p.y); // useful for sorting
    }

    bool operator==(const pt& p) const {
        return x == p.x and y == p.y;
    }
    // *** end of code for exact compares *** */
};

double dist(pt p1, pt p2) { // Euclidean distance
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(p1.x - p2.x, p1.y - p2.y); // return double
}

// returns true if point o is on the left side of line ab
bool ccw(pt a, pt b, pt o) { // algorithms are using me
    return o.cross(a, b) > EPS;
}

// returns true if point o is on the right side of line ab
bool cw(pt a, pt b, pt o) {
    return o.cross(a, b) < EPS;
}

// returns true if point o is on the same line as the line ab
bool collinear(pt a, pt b, pt o) {
    return abs(o.cross(a, b)) < EPS; // case for near values (doubles)
    // return o.cross(a, b) == 0; // case for exact values (ll)
}

pt_type sgn(pt_type val) { // return 1, 0 or -1 for positive, zero or negative values respectively
    return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

pt scale(pt v, double s) {     // non-negative s = [<1  ..  1 .. >1]
    return {v.x * s, v.y * s}; //                   shorter same longer
}

double angle(pt a, pt o, pt b) { // returns angle aob in rad
    return acos(o.dot(a, b) / sqrt((a - o).len_sqr() * (b - o).len_sqr()));
}

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double dist_to_line(pt p, pt a, pt b, pt& c) {
    // formula: c = a + u * ab
    pt ap = p - a, ab = b - a;
    double u = 1.0 * ap.dot(ab) / ab.len_sqr();
    c = a + scale(ab, u);
    return dist(p, c); // Euclidean distance between p and c
}

// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (byref)
double dist_to_line_segment(pt p, pt a, pt b, pt& c) {
    pt ap = p - a, ab = b - a;
    double u = 1.0 * ap.dot(ab) / ab.len_sqr();
    if (u < 0.0) {
        c = pt(a.x, a.y);  // closer to a
        return dist(p, a); // Euclidean distance between p and a
    }
    if (u > 1.0) {
        c = pt(b.x, b.y);  // closer to b
        return dist(p, b); // Euclidean distance between p and b
    }
    return dist_to_line(p, a, b, c); // run distToLine as above
}


struct line {
    double a, b, c;
}; // a way to represent a line

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(point p1, point p2, line& l) {
    if (fabs(p1.x - p2.x) < EPS) { // vertical line is fine
        l.a = 1.0;
        l.b = 0.0;
        l.c = -p1.x; // default values
    }
    else {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0; // IMPORTANT: we fix the value of b to 1.0
        l.c = -(double)(l.a * p1.x) - p1.y;
    }
}

// not needed since we will use the more robust form: ax + by + c = 0 (see above)
struct line2 {
    double m, c;
}; // another way to represent a line

int pointsToLine2(point p1, point p2, line2& l) {
    if (abs(p1.x - p2.x) < EPS) { // special case: vertical line
        l.m = INF;                // l contains m = INF and c = x_value
        l.c = p1.x;               // to denote vertical line x = x_value
        return 0;                 // we need this return variable to differentiate result
    }
    else {
        l.m = (double)(p1.y - p2.y) / (p1.x - p2.x);
        l.c = p1.y - l.m * p1.x;
        return 1; // l contains m and c of the line equation y = mx + c
    }
}

bool areParallel(line l1, line l2) { // check coefficients a & b
    return (fabs(l1.a - l2.a) < EPS) && (fabs(l1.b - l2.b) < EPS);
}

bool areSame(line l1, line l2) { // also check coefficient c
    return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS);
}

// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point& p) {
    if (areParallel(l1, l2))
        return false; // no intersection
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    // special case: test for vertical line to avoid division by zero
    if (fabs(l1.b) > EPS)
        p.y = -(l1.a * p.x + l1.c);
    else
        p.y = -(l2.a * p.x + l2.c);
    return true;
}


vector<pt> convex_hull(vector<pt> pts) {
    auto POP = [](stack<pt>& s) {
        pt p = s.top(); // this is just
        s.pop();        // such a really
        return p;       // painful API
    };

    // upper hull
    sort(pts.begin(), pts.end());
    stack<pt> stk_up;
    stk_up.push(pts[0]);
    stk_up.push(pts[1]);
    for (ull i = 2; i < pts.size(); i++) {
        while (stk_up.size() >= 2) {
            pt p = POP(stk_up);
            if (ccw(pts[i], p, stk_up.top())) {
                stk_up.push(p);
                break;
            }
        }
        stk_up.push(pts[i]);
    }

    // lower hull pre
    for (auto& p : pts) {
        p = -p;
    }
    // lower hull - c&p from upper hull, f&r (stk_up)->(stk_low)
    sort(pts.begin(), pts.end());
    stack<pt> stk_low;
    stk_low.push(pts[0]);
    stk_low.push(pts[1]);
    for (ull i = 2; i < pts.size(); i++) {
        while (stk_low.size() >= 2) {
            pt p = POP(stk_low);
            if (ccw(pts[i], p, stk_low.top())) {
                stk_low.push(p);
                break;
            }
        }
        stk_low.push(pts[i]);
    }

    // build convex hull
    vector<pt> ch;
    stk_low.pop();
    while (!stk_low.empty()) {
        ch.push_back(-POP(stk_low)); // note the minus
    }
    stk_up.pop();
    while (!stk_up.empty()) {
        ch.push_back(POP(stk_up));
    }
    // add one (not both) of those if needed
    rotate(ch.begin(), prev(ch.end()), ch.end()); // ccw from most left point
    // reverse(ch.begin(), ch.end()); // ccw -> cw from most left point
    return ch;
}

bool point_in_triangle(pt a, pt b, pt c, pt p) {
    pt_type s1 = fabs(a.cross(b, c)); // == triangle area, times 2
    pt_type s2 = fabs(p.cross(a, b)) + fabs(p.cross(b, c)) + fabs(p.cross(c, a));
    return fabs(s1 - s2) <= EPS;
}

// requires the result from convex hull in ccw order from the most left point
vector<pt> pre_point_in_convex_polygon(vector<pt>& pts) {
    /* // *** those lines can fix the convex hull if needed ***
    if (!ccw(pts[0], pts[1], pts[2])) {
        reverse(next(pts.begin()), pts.end());
    }
    ull pos = distance(pts.begin(), min_element(pts.begin(), pts.end()));
    rotate(pts.begin(), pts.begin() + pos, pts.end());
    // *** end of convex hull fix *** */

    vector<pt> seq;
    seq.reserve(pts.size());
    for (auto it = next(pts.begin()); it != pts.end(); ++it)
        seq.emplace_back((*it) - pts.front());
    seq.emplace_back(pts.front());
    return seq;
}

// requires the result from the pre function above
// the given point to check is normalized internally
bool point_in_convex_polygon(const vector<pt>& seq, pt p_) {
    pt base = seq.back();   // saved base is the last place in the seq
    ull n = seq.size() - 1; // effective size is (n-1), valid numbers range from 0 to (n-2)
    pt p = p_ - base;       // normalize the point using the base

    // normalized point has to be on the right side of the y-axis
    if (p.x < 0)
        return false;

    // case for when the point is on the same line as the start of the first segment
    pt_type s_p = seq[0].cross(p);
    if (s_p == 0)
        return seq[0].len_sqr() >= p.len_sqr() and seq[0].dot(p) >= 0;

    // case for when the point is on the same line as the end of the last segment
    pt_type l_p = seq[n - 1].cross(p);
    if (l_p == 0)
        return seq[n - 1].len_sqr() >= p.len_sqr() and seq[n - 1].dot(p) >= 0;

    // make sure the point is above the start of the first segment
    pt_type s_l = seq[0].cross(seq[n - 1]);
    if (sgn(s_p) != sgn(s_l))
        return false;

    // make sure the point is below the end of the last segment
    pt_type l_s = seq[n - 1].cross(seq[0]);
    if (sgn(l_p) != sgn(l_s))
        return false;

    // binary search for the angle the point is placed in
    ll l = 0, r = n - 1;
    while (r - l > 1) {
        ll mid = (l + r) / 2;
        if (seq[mid].cross(p) >= 0)
            l = mid;
        else
            r = mid;
    }
    ll pos = l;

    // check if the point is inside the triangle created there or outside of it
    return point_in_triangle(seq[pos], seq[pos + 1], pt(0, 0), p);
}

// requires the result from convex hull in ccw order (safer to make it from the most left point too)
#define INCN(x) ((x + 1) % n)
double minimum_width(vector<pt>& pts) {
    ull n = pts.size();

    if (n <= 2) // simple case
        return 0.0;

    double ret = INF;

    for (ull i = 0, j = 0; i < n; ++i) {
        while (pts[i].cross(pts[INCN(i)], pts[INCN(j)]) >= pts[i].cross(pts[INCN(i)], pts[j]))
            j = INCN(j);
        pt tmp{};
        double dist = dist_to_line(pts[j], pts[i], pts[INCN(i)], tmp);
        ret = min(ret, dist);
    }
    return ret;
}
