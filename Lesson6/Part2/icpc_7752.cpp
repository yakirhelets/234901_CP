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

int releaseFirstAndPut(int init, vector<int>& before, vector<int>& after) {
    int numOfActions=0;
    int n=init;
    while(before[n] == after[n] && before[before[n]-1] != 0) {
        n = before[n]-1;
    }
    if (before[before[n]-1] == 0) {
        numOfActions++;

    }
    before[n] = 0;

    return numOfActions;
}

/// XXXXX - Name
int main() {
    DO_LOAD_TEST(0);

    int n;
    while (cin >> n) {
        vector<int> before(n);
        for (int i=0 ; i<n ; i++) {
            int p;
            cin >> p;
            before[i] = p;
        }
        vector<int> after(n);
        for (int i=0 ; i<n ; i++) {
            int p;
            cin >> p;
            after[i] = p;
        }
        int numOfActions = 0;
        for (int i=0 ; i<n ; i++) {
            if (before[i] != after[i]) {
                if (before[i] != 0 && after[i] != 0) {
                    numOfActions+=releaseFirstAndPut(i, before, after);
                }
            }
        }
        for (int i=0 ; i<n ; i++) {
            if (before[i] != after[i]) {
                if (before[i] == 0) {
                    before[i] = after[i];
                    numOfActions++;
                } else {
                    if(after[i]==0) {
                        before[i] = after[i];
                        numOfActions++;
                    }
                }
            }
        }
        cout << numOfActions << endl;
    }
}
