#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <queue>
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


typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = INT32_MAX;

void bfs(const vvi &g, int s, vector<int> &d) {
    queue<int> q;
    q.push(s);
    vector<bool> visible(g.size(), false);
    visible[s] = true;
    d.assign(g.size(), INF);
    d[s] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (!visible[v]) {
                visible[v] = true;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
}

ull nChoosek(ull n, ull k) {
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    int result = n;
    for (ull i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}


/// 5221 - Page Hopping
int main() {
    DO_LOAD_TEST(1);

    ull tci = 1;
    while (true) {
        ull n1, n2;
        cin >> n1 >> n2;
        if (n1 == 0 && n2 == 0) { break; }
        vvi g(100);
        ull maxn = 100;
        while (true) {
            maxn = max(max(n1, n2), maxn);
            g[n1 - 1].push_back(n2 - 1);
            cin >> n1 >> n2;
            if (n1 == 0 && n2 == 0) { break; }
        }
        g.resize(maxn);

        vector<int> d;
        ull sum = 0;
        for (ull i = 0; i < g.size(); ++i) {
            bfs(g, i, d);
            for (int dd : d) {
                if (dd != INF) { sum += dd; }
            }
        }
        ull coun = 0;
        for (vi x : g) {
            if (x.size() > 0) { coun++; }
        }
        double x = 1.0 * sum / (nChoosek(coun, 2) * 2);
        cout << "Case " << tci << ": average length between pages = " << fixed << setprecision(3) << x << " clicks" << endl;
        tci++;
    }
}
