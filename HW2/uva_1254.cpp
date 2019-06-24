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


wstring SA_str; // the input string, up to 100K characters
vl RA, tempRA;  // rank array and temporary rank array
vl SA, tempSA;  // suffix array and temporary suffix array
vl c;           // for counting/radix sort
vl Phi, PLCP, LCP;


void countingSort(ll k) { // O(n)
    ll n = SA_str.size();
    ll i, sum, maxi = max(256LL * 256, n); // up to 255 ASCII chars or length of n
    c.assign(maxi, 0);
    for (i = 0; i < n; i++) // count the frequency of each integer rank
        c[i + k < n ? RA[i + k] : 0]++;
    for (i = sum = 0; i < maxi; i++) {
        ll t = c[i];
        c[i] = sum;
        sum += t;
    }
    for (i = 0; i < n; i++) // shuffle the suffix array if necessary
        tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    for (i = 0; i < n; i++) // update the suffix array SA
        SA[i] = tempSA[i];
}

void constructSA() { // this version can go up to 100000 characters
    ll n = SA_str.size();
    RA.assign(n, 0);
    tempRA.assign(n, 0);
    SA.assign(n, 0);
    tempSA.assign(n, 0);
    ll i, k, r;
    for (i = 0; i < n; i++)
        RA[i] = SA_str[i]; // initial rankings
    for (i = 0; i < n; i++)
        SA[i] = i;                // initial SA: {0, 1, 2, ..., n-1}
    for (k = 1; k < n; k <<= 1) { // repeat sorting process log n times
        countingSort(k);          // actually radix sort: sort based on the second item
        countingSort(0);          // then (stable) sort based on the first item
        tempRA[SA[0]] = r = 0;    // re-ranking; start from rank r = 0
        for (i = 1; i < n; i++)   // compare adjacent suffixes
            tempRA[SA[i]] =       // if same pair => same rank r; otherwise, increase r
                (RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
        for (i = 0; i < n; i++) // update the rank array RA
            RA[i] = tempRA[i];
        if (RA[SA[n - 1]] == n - 1)
            break; // nice optimization trick
    }
}

pair<ll, vl> computeLCP() {
    ll i, L;
    ll n = SA_str.size();
    Phi.assign(n, 0);
    PLCP.assign(n, 0);
    LCP.assign(n, 0);
    Phi[SA[0]] = -1;              // default value
    for (i = 1; i < n; i++)       // compute Phi in O(n)
        Phi[SA[i]] = SA[i - 1];   // remember which suffix is behind this suffix
    for (i = L = 0; i < n; i++) { // compute Permuted LCP in O(n)
        if (Phi[i] == -1) {
            PLCP[i] = 0;
            continue;
        } // special case
        while (SA_str[i + L] == SA_str[Phi[i] + L])
            L++; // L increased max n times
        PLCP[i] = L;
        L = max(L - 1, 0LL); // L decreased max n times
    }
    ll max_n = 1;
    vl idxs;
    LCP[0] = PLCP[SA[0]];     // put the permuted LCP to the correct position
    for (i = 1; i < n; i++) { // compute LCP in O(n)
        LCP[i] = PLCP[SA[i]]; // put the permuted LCP to the correct position
        bool a = SA_str.substr(SA[i]).find(L'$') != wstring::npos;
        bool b = SA_str.substr(SA[i - 1]).find(L'$') != wstring::npos;
        if (a != b) {
            idxs.push_back(i);
            max_n = max(max_n, LCP[i]);
        }
    }
    return make_pair(max_n, idxs);
}

/// 1254 - Top 10
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    DO_LOAD_TEST(0);

    ull n;
    cin >> n;
    cin.get();
    SA_str.reserve(100000 + 20000 + 1337);
    vl pos_to_index;
    pos_to_index.reserve(SA_str.capacity());
    vl index_to_length, index_to_start;
    index_to_length.reserve(20000 + 1);
    index_to_length.push_back(-1);
    index_to_start.reserve(20000 + 1);
    index_to_start.push_back(-1);
    for (ull i = 0; i < n; i++) {
        string s;
        getline(cin, s);
        SA_str.append(wstring(s.begin(), s.end()));
        SA_str.push_back(1337 + i);
        index_to_length.push_back(s.size());
        index_to_start.push_back(pos_to_index.size());
        for (ull j = 0; j < s.size() + 1; j++) {
            pos_to_index.push_back(i + 1);
        }
    }
    constructSA();

    ull q;
    cin >> q;
    cin.get();
    for (ull i = 0; i < q; i++) {
        string s;
        getline(cin, s);
        wstring ws(s.begin(), s.end());

        ll pmin, pmax;
        {
            ll l = 0, r = SA.size() - 1;
            while (r - l > 1) {
                ll mid = (l + r) / 2;
                ll pos = mid;
                if (ws.compare(SA_str.substr(SA[pos], ws.size())) > 0)
                    l = mid;
                else
                    r = mid;
            }
            pmin = (ws.compare(SA_str.substr(SA[l], ws.size())) > 0) ? r : l;
        }
        {
            ll l = 0, r = SA.size() - 1;
            while (r - l > 1) {
                ll mid = (l + r) / 2;
                ll pos = mid;
                if (ws.compare(SA_str.substr(SA[pos], ws.size())) >= 0)
                    l = mid;
                else
                    r = mid;
            }
            pmax = (ws.compare(SA_str.substr(SA[l], ws.size())) < 0) ? l : r;
        }
        size_t psize = pmax - pmin;

        if (psize == 0) {
            cout << -1 << endl;
            continue;
        }

        using lll = tuple<ll, ll, ll>;
        vector<lll> ranks;
        ranks.reserve(psize);
        unordered_set<ll> uniq;
        for (ull j = 0; j < psize; ++j) {
            ll idx = pos_to_index[SA[pmin + j]];
            if (uniq.find(idx) != uniq.end()) {
                continue;
            }
            uniq.insert(idx);
            ll len = index_to_length[idx];
            ll pos = index_to_start[idx];
            ranks.emplace_back(len, RA[pos], idx);
        }

        make_heap(ranks.begin(), ranks.end(), greater<lll>());
        bool first = true;
        for (ull j = 0; j < 10 and not ranks.empty(); ++j) {
            if (not first) {
                cout << " ";
            }
            first = false;
            pop_heap(ranks.begin(), ranks.end(), greater<lll>());
            auto largest = ranks.back();
            ranks.pop_back();
            cout << get<2>(largest);
        }
        cout << endl;
    }
}
