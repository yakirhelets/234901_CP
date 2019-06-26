#include <array>


using namespace std;

using ll = long long;
using ull = unsigned long long;


/// zero-based segment tree with T_N elements
using t_type = ll;
constexpr t_type T_START_V = 0;
constexpr t_type T_QUERY_V = 0;
#define T_OP +

template <ull N>
struct SegmentTree {
    array<t_type, 2 * N> ST = {T_START_V};

    void reset() { // reset tree
        ST = {T_START_V};
    }

    void init(ull i, t_type v) { // pre-build set value at position i
        ST[i + N] = v;
    }

    void build() { // build the tree in O(n)
        for (ull i = N - 1; i > 0; --i)
            ST[i] = ST[i << 1] T_OP ST[i << 1 | 1];
    }

    /// must have function. the rest are optional.
    void set(ull i, t_type v) { // post-build set value at position i
        for (ST[i += N] = v; i > 1; i >>= 1)
            ST[i >> 1] = ST[i] T_OP ST[i ^ 1];
    }

    /// must have function. the rest are optional.
    t_type query_r(ull l, ull r) { // from l to r inclusive on both ends
        t_type res = T_QUERY_V;
        for (l += N, r += N + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res = res T_OP ST[l++];
            if (r & 1)
                res = res T_OP ST[--r];
        }
        return res;
    }

    ll read(ull i) { // read value at position i
        return query_r(i, i);
    }

    void update(ull i, t_type d) { // post-build update value at position i
        set(i, read(i) + d);
    }

    void update_r(ull l, ull r, ll d) { // post-build update values from l to r inclusive on both ends
        for (ull i = l; i <= r; ++i)
            update(i, d);
    }
};
