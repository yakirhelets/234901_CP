#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;


// find the first x in [start, end] inclusive on both, such that [condition(x) == true]
// [start, end] should be sorted, such that there is only
// a single point at which [condition(i) == false] and [condition(i + 1) == true]
// condition can be `auto lower_bound = [arr, v](ull i) { return arr[i] >= v; };`
template <typename F>
ull bin_search(ull start, ull end, F condition) {
    ull l = start, r = end;
    while (l < r) {
        ull mid = (l + r) / 2;
        condition(mid) ? (r = mid) : (l = mid + 1);
    }
    return l; // first index that fulfils the condition
}

// print vector elements with space in between and end line after them
// vector cannot be empty!
template <typename T>
void print_vector(const vector<T>& v) {
    copy(v.begin(), prev(v.end()), ostream_iterator<T>(cout, " ")); // can change from space here
    cout << v.back() << endl;                                       // can remove new line here
}


int main() {
    ios_base::sync_with_stdio(false); // stop sync between cin/cout and scanf/printf
    cin.tie(nullptr); // stop flushing stdout whenever stdin is used

    vector<ull> arr = {1, 2, 3, 3, 3, 3, 5, 6};
    // v = 0   both   [v  v  v  v  v  v  v  v] -> arr[0] = 1; for both
    // v = 1   lb     [v  v  v  v  v  v  v  v] -> arr[0] = 1; for lb
    //         ub     [x  v  v  v  v  v  v  v] -> arr[1] = 2; for ub
    // v = 3   lb     [x  x  v  v  v  v  v  v] -> arr[2] = 3; for lb
    //         ub     [x  x  x  x  x  x  v  v] -> arr[6] = 5; for ub
    // v = 4   both   [x  x  x  x  x  x  v  v] -> arr[6] = 5; for both
    // v = 6   lb     [x  x  x  x  x  x  x  v] -> arr[7] = 6; for lb
    //         ub     [x  x  x  x  x  x  x  x] -> arr[7] = 6; for ub - special case
    // v = 9   both   [x  x  x  x  x  x  x  x] -> arr[7] = 6; for both

    for (ull v : {0, 1, 3, 4, 6, 9}) {
        auto lower_bound = [arr, v](ull i) { return arr[i] >= v; };
        auto upper_bound = [arr, v](ull i) { return arr[i] > v; };

        ull lb = bin_search(0, arr.size() - 1, lower_bound);
        ull ub = bin_search(0, arr.size() - 1, upper_bound);

        cout << v << " -> ";
        cout << "arr[" << lb << "] = " << arr[lb] << "; ";
        cout << "arr[" << ub << "] = " << arr[ub] << endl;
    }

    // iterate on all permutations
    vector<ll> p = {1, 2, 3};
    do { // 1 2 3 -> 1 3 2 -> 2 1 3 -> 2 3 1 -> 3 1 2 -> 3 2 1
        print_vector(p);
    } while (next_permutation(p.begin(), p.end()));
    print_vector(p); // ends back with 1 2 3
    cout << endl;
    vector<ll> q = {1, 3, 3};
    do { // 1 3 3 -> 3 1 3 -> 3 3 1
        print_vector(q);
    } while (next_permutation(q.begin(), q.end()));
    print_vector(q); // ends back with 1 3 3

    ll n1 = 123; n2 = 987;
    cout << min(n1, n2) << endl;
    cout << max(n1, n2) << endl;

    vector<ll> nums = {34, -125, 452, -23, 12, -54, 234, -627};
    cout << min_element(nums.begin(), nums.end()) << endl;
    cout << max_element(nums.begin(), nums.end()) << endl;
}
