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

ll findIndex(ll n) {
    const set<ll> fns = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987};
    if (n < 1000) {
        return distance(fns.begin(), fns.lower_bound(n));
    }
    double fibo = 2.078087 * log(n) + 1.672276;

    // returning rounded off value of index
    return floorl(fibo) - 1;
}

int getNumOfDigits(int n) {
    int i = 1;
    int j = 1;
    int temp;
    int numOfDigits = 1;
    while (n < j) {
        temp = j;
        j = j+i;
        i = temp;
        numOfDigits++;
    }
    return numOfDigits;
}

int getStartingIndex(int n) {
    int i = 1;
    int j = 1;
    int temp;
    int numOfDigits = 1;
    while (n < j) {
        temp = j;
        j = j+i;
        i = temp;
        numOfDigits++;
    }
    return numOfDigits;
}

// // vector<ll>&& FibonacciNumbers(ll n)
// // {
// //     ll f1 = 0, f2 = 1, i;

// //     vector<ll> fibnums;

// //     if (n < 1)
// //         return;

// //     while (f2 < n)
// //     {
// //         fibnums.push_back(f2);
// //         ll next = f1 + f2;
// //         f1 = f2;
// //         f2 = next;
// //     }
// //     return move(fibnums);
// // }


/// XXXXX - Name
int main() {
    DO_LOAD_TEST(0);

    int T;
    int N;
    int n;

    cin >> T;


    while (T--) {
        cin >> N;
        ll fn1, fn2 = findIndex(N);
        N -= fn2;
        cout << "1";
        while (N > 0) {
            ll fn1 = findIndex(N);
            for (size_t i = 0; i < fn2 - fn1 - 1; i++) {
                cout << "0";
            }
            N -= fn1;
        }
        for (size_t i = 0; i < fn2; i++) {
            cout << "0";
        }
        cout << endl;
    }
}
