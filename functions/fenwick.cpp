#include <array>

using namespace std;

using ll = long long;
using ull = unsigned long long;


/// zero-based Fenwick tree with N elements
template <ull N>
struct FenwickTree {
    array<ll, N + 1> FT = {0};

    void reset() { // reset tree
        FT = {0};
    }

    void init(ull i, ll v) { // pre-build set value at position i
        FT[i + 1] = v;
    }

    void build() { // build the tree in O(n)
        for (ull i = 1; i <= N; ++i) {
            ull j = i + (i & -i);
            if (j <= N)
                FT[j] += FT[i];
        }
    }

    /// must have function. the rest are optional.
    void update(ull i, ll d) { // post-build update value at position i
        for (++i; i <= N; i += i & -i)
            FT[i] += d;
    }

    /// must have function. the rest are optional.
    ll query_0i(ull i) { // query the tree from 0 to i inclusive on both ends
        ll sum = 0;
        for (++i; i > 0; i -= i & -i)
            sum += FT[i];
        return sum;
    }

    ll query_r(ull l, ull r) { // query the tree from l to r inclusive on both ends
        return query_0i(r) - query_0i(l - 1);
    }

    ll read(ull i) { // read value at position i
        return query_r(i, i);
    }

    void set(ull i, ll v) { // post-build set value at position i
        update(i, v - read(i));
    }

    void update_r(ull l, ull r, ll d) { // post-build update values from l to r inclusive on both ends
        for (ull i = l; i <= r; ++i)
            update(i, d);
    }
};


/// zero-based Fenwick tree with N elements, with range update. not good for big numbers.
template <ull N>
struct FenwickTree2 {
    FenwickTree<N + 1> FT1;
    FenwickTree<N + 1> FT2;

    void reset() { // reset tree
        FT1.reset();
        FT2.reset();
    }

    void init(ull i, ll v) { // pre-build set value at position i
        FT1.FT[i] = v;
    }

    void build() { // build the tree in O(n)
        for (ull v = 0, i = N; i > 0; --i) {
            v = FT1.FT[i];
            FT1.FT[i + 1] -= v;
            FT2.FT[i] += v * (i - 1);
            FT2.FT[i + 1] -= v * i;
        }
        FT1.build();
        FT2.build();
    }

    /// must have function. the rest are optional.
    void update_r(ull l, ull r, ll d) { // post-build update values from l to r inclusive on both ends
        FT1.update(l, d);
        FT1.update(r + 1, -d);
        FT2.update(l, d * (l - 1));
        FT2.update(r + 1, -d * r);
    }

    /// must have function. the rest are optional.
    ll query_0i(ull i) { // query the tree from 0 to i inclusive on both ends
        return FT1.query_0i(i) * i - FT2.query_0i(i);
    }

    ll query_r(ull l, ull r) { // query the tree from l to r inclusive on both ends
        return query_0i(r) - query_0i(l - 1);
    }

    ll read(ull i) { // read value at position i
        return query_r(i, i);
    }

    void update(ull i, ll d) { // post-build update value at position i
        update_r(i, i, d);
    }

    void set(ull i, ll v) { // post-build set value at position i
        update_r(i, i, v - read(i));
    }
};
