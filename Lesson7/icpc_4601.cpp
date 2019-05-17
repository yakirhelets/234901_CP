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


double s(vector<double>& a, size_t i) {
    double ax = a[i];
    double ay = a[i + 1];
    double bx = a[i + 2];
    double by = a[i + 3];
    double cx = a[i + 4];
    double cy = a[i + 5];
    return abs(ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)) / 2.0;
}

/// XXXXX - Name
int main() {
    DO_LOAD_TEST(0);

    double n;
    while (true) {
        vector<double> a;
        bool good = false;
        for (int i = 0; i < 12; ++i) {
            cin >> n;
            good |= (n != 0.0);
            a.push_back(n);
        }

        if (!good) {
            break;
        }

        double s1 = s(a, 0);
        double s2 = s(a, 6) / 2.0;
        double x = s2 / s1;
        double hx = x * (a[4] - a[0]) + a[0], hy = x * (a[5] - a[1]) + a[1];
        vector<double> b(a.begin(), a.begin() + 4);
        b.push_back(hx);
        b.push_back(hy);
        double s3 = s(b, 0);
        double gx = a[2] + (hx - a[0]), gy = a[3] + (hy - a[1]);

        cout << fixed << setprecision(3) << gx << " " << fixed << setprecision(3) << gy << " " << fixed
             << setprecision(3) << hx << " " << fixed << setprecision(3) << hy << endl;
    }
}
