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

template <typename K>
using uset = unordered_set<K>;
template <typename K, typename V>
using umap = unordered_map<K, V>;


using GK = string;
using wp = pair<ll, ll>;
using wgph = umap<GK, umap<GK, wp>>;
using gph = umap<GK, uset<GK>>;

using vgk = vector<GK>;

using gdist = umap<GK, wp>;


/********** Dijkstra **********/

// input: digraph (g), source (s)
// output: distances from s (dist)
void dijkstra(const wgph& g, const uset<GK>& all_v, const GK& s, gdist& dist) {
    constexpr wp INF = make_pair(INT64_MAX, INT64_MIN);
    dist = gdist();
    for (const auto& x : all_v) {
        dist[x] = INF;
    }
    dist[s] = make_pair(0, 0);
    priority_queue<pair<wp, GK>, vector<pair<wp, GK>>, greater<pair<wp, GK>>> q;
    q.push({dist[s], s});
    while (!q.empty()) {
        auto& front = q.top();
        wp d = front.first;
        GK u = front.second;
        q.pop();
        if (d > dist[u]) {
            continue;
        } // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        if (g.find(u) != g.end()) {
            for (const auto& next : (*g.find(u)).second) {
                GK v = next.first;
                wp w = next.second;
                wp new_w = make_pair(dist[u].first + w.first, dist[u].second + w.second);
                if (new_w < dist[v]) {
                    dist[v] = new_w;
                    q.push({dist[v], v});
                }
            }
        }
    }
}

vvpll memo;
vector<wp> items;
pll f(ll i, ll c) {
    if (memo[i][c] != make_pair(-1LL, -1LL))
        return memo[i][c];
    if (i == 0 || c == 0)
        return make_pair(0LL, 0LL);
    if (items[i].first <= c) {
        auto res = f(i - 1, c - items[i].first);
        return memo[i][c] = min(f(i - 1, c), make_pair(items[i].second + res.first, items[i].first + res.second));
    }
    return memo[i][c] = f(i - 1, c);
}


/// 8149 - Ingredients
int main() {
    DO_LOAD_TEST(1);

    ull b, n;
    while (cin >> b >> n) {
        wgph from_x_to_ys;
        uset<GK> res_only;
        uset<GK> all_v;
        for (ull i = 0; i < n; ++i) {
            string res, base, ing;
            ll cost, prs;
            cin >> res >> base >> ing >> cost >> prs;
            res_only.insert(res);
            all_v.insert(base);
            all_v.insert(res);
            auto w = make_pair(cost, -prs);
            if (from_x_to_ys.find(base) == from_x_to_ys.end()) {
                from_x_to_ys[base] = {};
            }
            if (from_x_to_ys[base].find(res) != from_x_to_ys[base].end()) {
                if (from_x_to_ys[base][res].first < w.first) {
                    continue;
                }
                if (from_x_to_ys[base][res].first == w.first and from_x_to_ys[base][res].second < w.second) {
                    continue;
                }
            }
            from_x_to_ys[base][res] = w;
        }

        const string start = "start!";
        uset<GK> base_only;
        for (const auto& x : from_x_to_ys) {
            if (res_only.find(x.first) != res_only.end()) {
                continue;
            }
            base_only.insert(x.first);
        }
        from_x_to_ys[start] = {};
        for (const auto& x : base_only) {
            from_x_to_ys[start][x] = make_pair(0, 0);
        }

        gdist dist;
        dijkstra(from_x_to_ys, all_v, start, dist);
        items = {};
        items.emplace_back(-1, -1);
        for (const auto& x : dist) {
            if (x.second.first == 0 and x.second.second == 0) {
                continue;
            }
            if (x.second.first == INT64_MAX and x.second.second == INT64_MIN) {
                continue;
            }
            items.push_back(x.second);
            // cout << x.first << " " << x.second.first << "," << x.second.second << endl;
        }

        memo = {items.size(), vpll(b + 1, {-1, -1})};
        auto ans = f(items.size() - 1, b);
        cout << -ans.first << endl << ans.second << endl;
    }
}
