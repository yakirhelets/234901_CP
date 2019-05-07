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


ll powmodn(ll a, ll q, ll n) {
    ll res = 1;
    while (q) {
        if (q % 2)
            res = (res * a) % n;
        a = (a * a) % n;
        q >>= 1;
    }
    return res;
}

/// XXXXX - Name
int main() {
    DO_LOAD_TEST(0);

    ull n, m;
    while (cin >> n >> m) {
        char c;
        ull t = 0;
        ull x = 0;
        while (n--) {
            cin >> c;
            ull cc = c - '0';
            t = 10 * t + cc;
            t %= m;
            if (t == 0) {
                ++x;
            }
        }
        if (t != 0 || x == 0) {
            cout << 0 << endl;
        } else {
            cout << powmodn(2, x - 1, 1000000007LL) << endl;
        }
    }
}
