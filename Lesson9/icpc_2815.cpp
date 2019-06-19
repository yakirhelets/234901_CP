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

vvl memo;

ull solve(const vvl& x, ull l, ull m) {
    if (memo[l][m] != -1)
        return memo[l][m];
    if (m == 1 and l == 1)
        return memo[l][m] = x[l][m];
    if (m == 1)
        return memo[l][m] = x[l][m] + solve(x, l - 1, m);
    if (l == 1)
        return memo[l][m] = x[l][m] + solve(x, l, m - 1);
    return memo[l][m] = x[l][m] + max(solve(x, l, m - 1), solve(x, l - 1, m));
}


/// XXXXX - Name
int main() {
    DO_LOAD_TEST(0);

    ull n;
    while (cin >> n) {
        if (n == 0) {
            break;
        }
        vvl x(101, vl(101, 0));
        for (ull i = 0; i < n; ++i) {
            ull l, m;
            cin >> l >> m;
            x[l][m]++;
        }
        memo = vvl(101, vl(101, -1));
        cout << solve(x, 100, 100) << endl;
    }
    cout << "*" << endl;
}
