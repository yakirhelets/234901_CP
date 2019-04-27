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



int main() {
    DO_LOAD_TEST(0);

    int T;
    int N;

    cin >> T;

    vector<int> fib = {1,1};
    for (int i = 2 ; i < 45 ; i++) { //45 is max int
        fib.push_back(fib[i-1] + fib[i-2]);
    }

    while (T--) {
        cin >> N;
        int biggetLessThanN=44;

        while (fib[biggetLessThanN] > N) {
            biggetLessThanN--;
        }

        for (int i=biggetLessThanN; i>=1; i--){
            if(fib[i] <= N){
                cout << "1";
                N -= fib[i];
            } else {
                cout << "0";
            }
        }
        cout << endl;
    }
    return 0;
}
