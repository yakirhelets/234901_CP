#include <vector>

using namespace std;

using ull = unsigned long long;

struct UnionFind {
    vector<ull> rank;
    vector<ull> parent;

    explicit UnionFind(ull size) {
        rank = vector<ull>(size, 0);
        parent = vector<ull>(size);
        for (ull i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    ull find(ull x) {
        ull tmp = x; // variable only used in log* code
        while (x != parent[x]) {
            x = parent[x];
        }
        while (tmp != x) { // for log*, not needed most of the time
            ull next = parent[tmp];
            parent[tmp] = x;
            tmp = next;
        } // end of log* code
        return x;
    }

    void unite(ull p, ull q) {
        p = find(p);
        q = find(q);
        if (q == p) { // already in the same group
            return;
        }
        if (rank[p] < rank[q]) { // add shorter to longer
            parent[p] = q;
        }
        else {
            parent[q] = p;
        }
        if (rank[p] == rank[q]) { // update rank if needed
            rank[p]++;
        }
    }
};
