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


struct point {
    ll x, y;
    point() : x(0), y(0) {
    }
    point(ll _x, ll _y) : x(_x), y(_y) {
    }
    point operator+(const point& p) const {
        return {x + p.x, y + p.y};
    }
    point operator-(const point& p) const {
        return {x - p.x, y - p.y};
    }
    bool operator<(point other) const {
        return (x < other.x) ? true : ((x == other.x) and (y < other.y));
    }
    bool operator==(point other) const {
        return (x == other.x) and (y == other.y);
    }
};


/// 105 - The Skyline Problem
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    DO_LOAD_TEST(3);

    using l3 = tuple<ll, ll, ll>;
    vector<l3> buildings;
    map<ll, vector<ull>> lines;
    ll bl, br, bh;
    while (cin >> bl >> bh >> br) {
        buildings.emplace_back(bl, br, bh);
    }

    for (ull i = 0; i < buildings.size(); ++i) {
        lines[get<0>(buildings[i])].emplace_back(i);
        lines[get<1>(buildings[i])].emplace_back(i);
    }

    ll x, y;
    cin >> x >> y;

    vector<bool> q;
    q.assign(buildings.size(), false);
    vector<ll> skyline;
    multiset<ll> live;
    ll current_height = 0;

    // special case if there is no building at the start.
    if (lines.begin()->first > 1) {
        skyline.push_back(1);
        skyline.push_back(0);
    }
    for (auto& line : lines) {
        ll right = line.first;
        // go over all the buildings that start/end on this line.
        for (auto idx : line.second) {
            ll h = get<2>(buildings[idx]);
            if (q[idx]) {
                // this is the end of this building
                live.erase(live.lower_bound(h));
            }
            else {
                // this is the start of this building
                live.insert(h);
            }
            q[idx] = !q[idx];
        }

        // check if the height have changed
        ll new_height = live.empty() ? 0 : *live.rbegin();
        if (new_height != current_height) {
            current_height = new_height;
            skyline.push_back(right);
            skyline.push_back(current_height);
        }
    }

    std::copy(skyline.begin(), prev(skyline.end()), std::ostream_iterator<ll>(cout, " "));
    cout << skyline.back() << endl;
}
