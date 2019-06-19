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
using vvvl = vector<vvl>;

using sl = set<ll>;
using vsl = vector<sl>;

constexpr ll INV = 9999;


/// 2728 - A Spy in the Metro
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    DO_LOAD_TEST(0);

    ull n;
    ull tci = 1;
    while (cin >> n) {
        if (n == 0) {
            break;
        }

        ull t;
        cin >> t;

        vvl memo = vvl(n + 1, vl(t + 1, INV));
        memo[1][0] = 0;

        vl delta_t(n);
        for (ull i = 1; i <= n - 1; ++i) {
            ll ti;
            cin >> ti;
            delta_t[i] = ti;
        }

        vvvl trains(n + 1, vvl(t + 1, vl(2, -1)));
        ull m1;
        cin >> m1;
        for (ull i = 1; i <= m1; ++i) {
            ull m;
            cin >> m;
            for (ull j = 1; j < n and m < t; ++j) {
                ll dt = delta_t[j];
                trains[j][m][0] = dt;
                m += dt;
            }
        }

        ull m2;
        cin >> m2;
        for (ull i = 1; i <= m2; ++i) {
            ull m;
            cin >> m;
            for (ull j = n; j > 1 and m < t; --j) {
                ll dt = delta_t[j - 1];
                trains[j][m][1] = dt;
                m += dt;
            }
        }

        for (ull tt = 0; tt < t; ++tt) {
            for (ull ss = 1; ss <= n; ++ss) {
                memo[ss][tt + 1] = min(memo[ss][tt + 1], memo[ss][tt] + 1);
                if (trains[ss][tt][0] != -1) {
                    ll dt = trains[ss][tt][0];
                    if (tt + dt <= t) {
                        memo[ss + 1][tt + dt] = min(memo[ss + 1][tt + dt], memo[ss][tt]);
                    }
                }
                if (trains[ss][tt][1] != -1) {
                    ll dt = trains[ss][tt][1];
                    if (tt + dt <= t) {
                        memo[ss - 1][tt + dt] = min(memo[ss - 1][tt + dt], memo[ss][tt]);
                    }
                }
            }
        }

        cout << "Case Number " << tci++ << ": ";
        if (memo[n][t] != INV) {
            cout << memo[n][t] << endl;
        }
        else {
            cout << "impossible" << endl;
        }
    }
}
