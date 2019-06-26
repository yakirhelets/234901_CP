/* -----------------------------
 * ------------ STL ------------
   ----------------------------- */

/*** Useful to include ***/
#include <bits/stdc++.h>


/* -----------------------------
 * ------ DATA STRUCTURES ------
   ----------------------------- */

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

/** Fenwick **/
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


/** Segment **/
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


/** Union-Find **/
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



/* -----------------------------
 * ------- NUMBER THEORY -------
   ----------------------------- */


/* -----------------------------
 * ---------- GRAPHS -----------
   ----------------------------- */

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <stack>

using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

/*** BFS ***/
void bfs(const vvi& g, int s) {
    queue<int> q; q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        printf("%d\n", u);
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                q.push(v);
            }}}

/*** DFS ***/
void dfs(const vvi& g, int s) {
    stack<int> q; q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    while (!q.empty()) {
        int u = q.top(); q.pop();
        printf("%d\n", u);
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                q.push(v);
            }}}


/*** DFS - Recursive ***/
vvi g;
vector<bool> visible;
void dfs_recursive(int s) {
    printf("%d\n", s);
    visible[s] = true;
    for(int u : g[s]) if(!visible[u]) dfs_recursive(u);
}
//In main:
//// load graph to g
//visible.assign(g.size(),false);
//dfs(0);

/********** Topological Sort **********/
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: is g a DAG (return value), a topological ordering of g (order).
// comment: order is valid only if g is a DAG.
// time: O(V+E).
bool topological_sort(const vvi& g, vi& order) {
    // compute indegree of all nodes
    vi indegree (g.size(), 0);
    for (int v=0; v<g.size(); v++) for (int u : g[v]) indegree[u]++;
    // order sources first
    order = vector<int>();
    for (int v=0; v<g.size(); v++) if (indegree[v] == 0) order.push_back(v);
    // go over the ordered nodes and remove outgoing edges,
    // add new sources to the ordering
    for (int i=0; i<order.size(); i++) for (int u : g[order[i]]) {
            indegree[u]--;
            if (indegree[u]==0) order.push_back(u);
        }
    return order.size()==g.size();
}


/********** Strongly Connected Components **********/
const int UNSEEN = -1;
const int SEEN = 1;

void KosarajuDFS(const vvi& g, int u, vi& S, vi& colorMap, int color) {
    // DFS on digraph g from node u:
    // visit a node only if it is mapped to the color UNSEEN,
    // Mark all visited nodes in the color map using the given color.
    // input: digraph (g), node (v), mapping:node->color (colorMap), color (color).
    // output: DFS post-order (S), node coloring (colorMap).
    colorMap[u] = color;
    for (auto& v : g[u])
        if (colorMap[v] == UNSEEN)
            KosarajuDFS(g, v, S, colorMap, color);
    S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: the number of SCCs (return value), a mapping from node to SCC color (components).
// time: O(V+E).
int findSCC(const vvi& g, vi& components) {
    // first pass: record the `post-order' of original graph
    vi postOrder, seen;
    seen.assign(g.size(), UNSEEN);
    for (int i = 0; i < g.size(); ++i)
        if (seen[i] == UNSEEN)
            KosarajuDFS(g, i, postOrder, seen, SEEN);
    // second pass: explore the SCCs based on first pass result
    vvi reverse_g(g.size(),vi());
    for (int u=0; u<g.size(); u++) for (int v : g[u]) reverse_g[v].push_back(u);
    vi dummy;
    components.assign(g.size(), UNSEEN);
    int numSCC = 0;
    for (int i = (int)g.size()-1; i >= 0; --i)
        if (components[postOrder[i]] == UNSEEN)
            KosarajuDFS(reverse_g, postOrder[i], dummy, components, numSCC++);
    return numSCC;
}

// Computes the SCC graph of a given digraph.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: strongly connected components graph of g (sccg).
// time: O(V+E).
void findSCCgraph(const vvi& g, vsi& sccg) {
    vi component;
    int n = findSCC(g, component);
    sccg.assign(n, si());
    for (int u=0; u<g.size(); u++) for (int v: g[u]) // for every edge u->v
            if (component[u] != component[v])
                sccg[component[u]].insert(component[v]);
}


/********** Shortest Paths **********/
// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source (s).
// output: distances from s (dist).
// time: O(ElogV).
void Dijkstra(const vvii& g, int s, vi& dist) {
    dist = vi(g.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top(); q.pop();
        int d = front.first, u = front.second;
        if (d > dist[u]) continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (ii next : g[u]) {
            int v = next.first, w = next.second;
            if (dist[u]+w < dist[v]) {
                dist[v] = dist[u]+w;
                q.push({dist[v], v});
            }
        }
    }
}

// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1), source node (s).
// output: is there a negative cycle in g? (return value), the distances from s (d)
// comment: the values in d are valid only if there is no negative cycle.
// time: O(VE).
bool BellmanFord(const vvii& g, int s, vi& d) {
    d.assign(g.size(), INF);
    d[s] = 0;
    bool changed = false;
    // V times
    for (int i = 0; i < g.size(); ++i) {
        changed = false;
        // go over all edges u->v with weight w
        for (int u = 0; u < g.size(); ++u) for (ii e : g[u]) {
                int v = e.first;
                int w = e.second;
                // relax the edge
                if (d[u] < INF && d[u]+w < d[v]) {
                    d[v] = d[u]+w;
                    changed = true;
                }
            }
    }
    // there is a negative cycle if there were changes in the last iteration
    return changed;
}

// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named 0,1,...,|V|-1).
// output: the pairwise distances (d).
// time: O(V^3).
void FloydWarshall(const vvii& g, vvi& d) {
    // initialize distances according to the graph edges
    d.assign(g.size(), vi(g.size(), INF));
    for (int u=0; u<g.size(); ++u) d[u][u] = 0;
    for (int u=0; u<g.size(); ++u) for (ii e: g[u]) {
            int v = e.first; int w = e.second;
            d[u][v] = min(d[u][v],w);
        }
    // relax distances using the Floyd-Warshall algorithm
    for (int k=0; k<g.size(); ++k)
        for (int u=0; u<g.size(); ++u)
            for (int v=0; v<g.size(); ++v)
                d[u][v] = min(d[u][v], d[u][k]+d[k][v]);
}


/********** Min Spanning Tree **********/
struct unionfind {
    vector<int> rank;
    vector<int> parent;

    unionfind (int size) {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++) parent[i]=i;
    }

    int find(int x) {
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x) {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }

    void unite(int p, int q) {
        p = find(p);
        q = find(q);
        if(q==p) return;
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};


// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (n), all nodes are between 0 and n-1.
// output: weight of a minimum spanning tree.
// time: O(ElogV).
int Kruskal(vector<iii>& edges, int n) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0;
    unionfind components(n);
    for (iii e : edges) {
        if (components.find(e.second.first) != components.find(e.second.second)) {
            mst_cost += e.first;
            components.unite(e.second.first, e.second.second);
        }
    }
    return mst_cost;
}


/********** Max Flow **********/
int augment(vvi& res, int s, int t, const vi& p, int minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
        res[p[t]][t] -= f;
        res[t][p[t]] += f;
        return f;
    }
    return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp (int n, vector<iii>& edges, int s, int t) {
    // initialise adjacenty list and residuals adjacency matrix
    vvi res(n,vi(n,0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
        }
        // add flow on the path between s to t according to p
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}

/* -----------------------------
 * --------- GEOMETRY ----------
   ----------------------------- */


/* -----------------------------
 * --------- STRINGS -----------
   ----------------------------- */