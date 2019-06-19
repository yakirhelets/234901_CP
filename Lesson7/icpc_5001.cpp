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


/// 5001 - Making Quadrilaterals
int main() {
    DO_LOAD_TEST(0);

    vector<ll> a;
    a.push_back(1);
    a.push_back(1);
    a.push_back(1);
    for (size_t i = 0; i < 70; i++) {
        a.push_back(a[i] + a[i + 1] + a[i + 2]);
    }

    ull n;
    ull i = 1;
    while (cin >> n) {
        if (n == 0) {
            break;
        }

        cout << "Case " << i++ << ": " << a[n - 1] << endl;
    }
}
