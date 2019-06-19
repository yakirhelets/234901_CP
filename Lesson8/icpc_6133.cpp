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


/// XXXXX - Name
int main() {
    DO_LOAD_TEST(0);
}
