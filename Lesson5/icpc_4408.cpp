#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <queue>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
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


/// 4408 - Unlock the Lock
int main() {
    DO_LOAD_TEST(0);

    ull tci = 1;
    while (true) {
        ull n1, n2, n3;
        cin >> n1 >> n2 >> n3;
        if (n1 == 0 && n2 == 0 && n3 == 0) { break; }
        vi ops;
        while (n3--) {
            ull n;
            cin >> n;
            ops.push_back(n);
        }
        queue<int> q;
        set<int> ccc;
        ccc.insert(n1);
        q.push(n1);
        vi d;
        d.assign(10000, INF);
        d[n1] = 0;
        bool flag = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int v : ops) {
                int res = (u + v) % 10000;
                if (ccc.find(res) != ccc.end()) {
                    continue;
                }
                ccc.insert(res);
                d[res] = d[u] + 1;
                q.push(res);
            }
            if (ccc.find(n2) != ccc.end()) {
                flag = true;
                break;
            }
        }
        cout << "Case " << tci++ << ": ";
        if (flag) {
            cout << d[n2] << endl;
        } else {
            cout << "Permanently Locked" << endl;
        }
    }
}
