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


const ull MAX_F = (1ULL << 34ULL);
vector<ull> fibs;


void rq(ull n, ull i, ull j) {
    if (n >= fibs.size()) {
        return rq(fibs.size() + ((n + 1) % 2) - 2, i, j);
    }
    if (n == 0) {
        assert(i == j and i == 0);
        cout << "0";
        return;
    }
    if (n == 1) {
        assert(i == j and i == 0);
        cout << "1";
        return;
    }
    if (j < fibs[n - 2]) {
        return rq(n - 2, i, j);
    }
    if (i >= fibs[n - 2]) {
        return rq(n - 1, i - fibs[n - 2], j - fibs[n - 2]);
    }
    rq(n - 2, i, fibs[n - 2] - 1);
    rq(n - 1, 0, j - fibs[n - 2]);
}

/// 12041 - BFS (Binary Fibonacci String)
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    DO_LOAD_TEST(1);

    fibs.push_back(1);
    fibs.push_back(1);


    for (sz i = fibs.size() - 1; fibs[i] <= MAX_F; i++) {
        fibs.push_back(fibs[i] + fibs[i - 1]);
    }

    ull t;
    cin >> t;
    while (t--) {
        ull n, i, j;
        cin >> n >> i >> j;
        rq(n, i, j);
        cout << endl;
    }
    return 0;
}
