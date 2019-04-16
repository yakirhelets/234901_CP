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


vector<bool> sieve(ll n) {
    vector<bool> ps(n + 1, true);
    ps[0] = false;
    ps[1] = false;
    ll sqrtn = sqrt(n);
    for (ll i = 0; i <= sqrtn; ++i) {
        if (ps[i]) {
            for (ll j = i * i; j <= n; j += i) {
                ps[j] = false;
            }
        }
    }
    return ps;
}

bool isPrime(ll n){
    if(n<2)
        return false;
    ll sqrtn = sqrt(n);
    for (ll i = 2; i <= sqrtn; ++i) {
        if(n%i == 0){
            return false;
        }
    }
    return true;
}


/// XXXXX - Name
int main() {
    DO_LOAD_TEST(0);

    bool first = true;

    ll L, U;

    // vector<bool> PP = sieve(1000000);


    while (cin >> L >> U) 
    {
        if (!first)
            cout << '\n';

       first = false;

        vector<ll> P;

        P.reserve(U);

        for (size_t i = L; i <= U; i++) 
        {
            
            // if (i < 1000000) {
            //     if (PP[i])
            //         P.push_back(i);
            // }
            // else
            // {
                if (isPrime(i)) P.push_back(i);
        }

        if (P.size() < 2) {
            cout << "There are no adjecent primes.";
            continue;
        }

        ll d1;
        ll d2;
        ll ddist = -1;

        ll dist = INFINITY;
        ll c1, c2;
        ll psize = P.size();
        for (ll i = 1; i < psize; i++) {
            if (P[i] - P[i - 1] < dist) {
                c1 = P[i - 1];
                c2 = P[i];
                dist = P[i] - P[i - 1];
            }
            if (P[i] - P[i - 1] > ddist) {
                d1 = P[i - 1];
                d2 = P[i];
                ddist = P[i] - P[i - 1];
            }
        }
        cout << c1 << "," << c2 << " are closest. " << d1 << "," << d2 << " are most distant.";
    }
    return 0;
}
