#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
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


vector<bool> sieve(int n) {
    vector<bool> ps(n + 1, true);
    ps[0] = false;
    ps[1] = false;
    int sqrtn = sqrt(n);
    for (int i = 0; i <= sqrtn; ++i) {
        if (ps[i]) {
            for (int j = i * i; j <= n; j += i) {
                ps[j] = false;
            }
        }
    }
    return ps;
}

constexpr ll N = 10001;

/// XXXXX - Name
int main() {
    DO_LOAD_TEST(0);

    vector<bool> PP = sieve(N);
    vector<ll> P, C(N);
    P.reserve(N);
    for (size_t i = 0; i < PP.size(); i++) {
        if (PP[i]) {
            P.push_back(i);
        }
    }
    for (size_t i = 1; i <= P.size(); i++) {
        for (size_t j = 0; j < P.size() - i + 1; j++) {
            ll sum = 0;
            for (size_t k = 0; k < i; k++) {
                sum += P[j + k];
            }
            if (sum < N) {
                C[sum] += 1;
            }
        }
    }
    
    ll inp;
    while(true) {
        cin >> inp;
        if (inp == 0) {
            break;
        }
        cout << C[inp] << endl;
    }
}
