#include <algorithm>
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

#define EPS 1e-9

struct pt{
    ll x, y;
    pt(){}
    pt(ll _x, ll _y):x(_x), y(_y){}
    pt operator+(const pt & p) const { return pt(x + p.x, y + p.y); }
    pt operator-(const pt & p) const { return pt(x - p.x, y - p.y); }
    ll cross(const pt & p) const { return x * p.y - y * p.x; }
    ll dot(const pt & p) const { return x * p.x + y * p.y; }
    ll cross(const pt & a, const pt & b) const { return (a - *this).cross(b - *this); }
    ll dot(const pt & a, const pt & b) const { return (a - *this).dot(b - *this); }
    ll sqrLen() const { return this->dot(*this); }
};

bool lexComp(const pt & l, const pt & r){
//    return l.x < r.x || (l.x == r.x && l.y < r.y);
    if (fabs(l.x - r.x) > EPS) {
        return (l.x < r.x);
    } else {
        return (l.y < r.y);
    }
}

int sgn(ll val){
    return val > 0 ? 1 : (val == 0 ? 0 : -1);
}

vector<pt> seq;
int n;

bool pointInTriangle(pt a, pt b, pt c, pt point){
    ll s1 = abs(a.cross(b, c));
    ll s2 = abs(point.cross(a, b)) + abs(point.cross(b, c)) + abs(point.cross(c, a));
    return s1 == s2;
}

void prepare(vector<pt> & points){
    n = points.size();
    int pos = 0;
    for(int i = 1; i < n; i++){
        if(lexComp(points[i], points[pos]))
            pos = i;
    }
    rotate(points.begin(), points.begin() + pos, points.end());

    n--;
    seq.resize(n);
    for(int i = 0; i < n; i++)
        seq[i] = points[i + 1] - points[0];
}

bool pointInConvexPolygon(pt point){
//    cout << seq[0].cross(point) << endl;
//    cout << seq[0].cross(seq[n - 1]) << endl;
    if(seq[0].cross(point) != 0 && sgn(seq[0].cross(point)) != sgn(seq[0].cross(seq[n - 1])))
        return false;
    if(seq[n - 1].cross(point) != 0 && sgn(seq[n - 1].cross(point)) != sgn(seq[n - 1].cross(seq[0])))
        return false;

    if(seq[0].cross(point) == 0)
        return seq[0].sqrLen() >= point.sqrLen();

    int l = 0, r = n - 1;
    while(r - l > 1){
        int mid = (l + r)/2;
        int pos = mid;
        if(seq[pos].cross(point) >= 0)l = mid;
        else r = mid;
    }
    int pos = l;
    return pointInTriangle(seq[pos], seq[pos + 1], pt(0, 0), point);
}



//bool cmp(pt a, pt b) {
//    return a.x < b.x || (a.x == b.x && a.y < b.y);
//}

bool cw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<pt>& a) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end(), &lexComp);
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}


/// XXXXX - Name
int main() {
    DO_LOAD_TEST(0);

    ull L, S;

    while(cin >> L) {
        vector<pt> pts1;
        for (ull i = 0; i < L; ++i) {
            ull x, y;
            cin >> x >> y;
            pts1.emplace_back(x, y);
        }

        cin >> S;
        vector<pt> pts2;
        for (ull i = 0; i < S; ++i) {
            ull x, y;
            cin >> x >> y;
            pts2.emplace_back(x, y);
        }

        convex_hull(pts1);



//        reverse(++pts1.begin(), pts1.end());
        seq = pts1;
        prepare(seq);

        ull counter = 0;
        for (auto& p : pts2) {
            counter += pointInConvexPolygon(p) ? 1 : 0;
        }

        cout << counter << endl;
    }
}
