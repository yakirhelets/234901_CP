// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli. Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

#include <algorithm>
#include <queue>
#include <set>
#include <vector>

using namespace std;

using ll = long long;
using ull = unsigned long long;

typedef pair<ll, ll> ii;
typedef pair<ll, ii> iii;

typedef vector<ii> vii;
typedef vector<vii> vvii;

typedef vector<ll> vi;
typedef vector<vi> vvi;

typedef set<ll> si;
typedef vector<si> vsi;

const ll INF = 1e9;


/********** Topological Sort **********/


// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: is g a DAG (return value), a topological ordering of g (order).
// comment: order is valid only if g is a DAG.
// time: O(V+E).
bool topological_sort(const vvi& g, vi& order) {
    // compute indegree of all nodes
    vi indegree(g.size(), 0);
    for (const vi& v : g)
        for (ll u : v)
            indegree[u]++;
    // order sources first
    order = vector<ll>();
    for (ull v = 0; v < g.size(); v++)
        if (indegree[v] == 0)
            order.push_back(v);
    // go over the ordered nodes and remove outgoing edges,
    // add new sources to the ordering
    for (ull i = 0; i < order.size(); i++)
        for (ll u : g[order[i]]) {
            indegree[u]--;
            if (indegree[u] == 0)
                order.push_back(u);
        }
    return order.size() == g.size();
}


/********** Strongly Connected Components **********/


const ll UNSEEN = -1;
const ll SEEN = 1;

void KosarajuDFS(const vvi& g, ll u, vi& S, vi& colorMap, ll color) {
    // DFS on digraph g from node u:
    // visit a node only if it is mapped to the color UNSEEN,
    // Mark all visited nodes in the color map using the given color.
    // input: digraph (g), node (v), mapping:node->color (colorMap), color (color).
    // output: DFS post-order (S), node coloring (colorMap).
    colorMap[u] = color;
    for (ll v : g[u])
        if (colorMap[v] == UNSEEN)
            KosarajuDFS(g, v, S, colorMap, color);
    S.push_back(u);
}

// Compute the number of SCCs and maps nodes to their corresponding SCCs.
// input: directed graph (g[u] contains the neighbors of u, nodes are named 0,1,...,|V|-1).
// output: the number of SCCs (return value), a mapping from node to SCC color (components).
// time: O(V+E).
ll findSCC(const vvi& g, vi& components) {
    // first pass: record the `post-order' of original graph
    vi postOrder, seen;
    seen.assign(g.size(), UNSEEN);
    for (ll i = 0; i < g.size(); ++i)
        if (seen[i] == UNSEEN)
            KosarajuDFS(g, i, postOrder, seen, SEEN);
    // second pass: explore the SCCs based on first pass result
    vvi reverse_g(g.size(), vi());
    for (ll u = 0; u < g.size(); u++)
        for (ll v : g[u])
            reverse_g[v].push_back(u);
    vi dummy;
    components.assign(g.size(), UNSEEN);
    ll numSCC = 0;
    for (ll i = g.size() - 1; i >= 0; --i)
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
    ll n = findSCC(g, component);
    sccg.assign(n, si());
    for (ll u = 0; u < g.size(); u++)
        for (ll v : g[u]) // for every edge u->v
            if (component[u] != component[v])
                sccg[component[u]].insert(component[v]);
}


/********** Shortest Paths **********/


// input: non-negatively weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named
// 0,1,...,|V|-1), source (s). output: distances from s (dist). time: O(ElogV).
void Dijkstra(const vvii& g, ll s, vi& dist) {
    dist = vi(g.size(), INF);
    dist[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top();
        q.pop();
        ll d = front.first, u = front.second;
        if (d > dist[u])
            continue; // We may have found a shorter way to get to u after inserting it to q.
        // In that case, we want to ignore the previous insertion to q.
        for (ii next : g[u]) {
            ll v = next.first, w = next.second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                q.push({dist[v], v});
            }
        }
    }
}

// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named
// 0,1,...,|V|-1), source node (s). output: is there a negative cycle in g? (return value), the distances from s (d)
// comment: the values in d are valid only if there is no negative cycle. time: O(VE).
bool BellmanFord(const vvii& g, ll s, vi& d) {
    d.assign(g.size(), INF);
    d[s] = 0;
    bool changed = false;
    // V times
    for (ull i = 0; i < g.size(); ++i) {
        changed = false;
        // go over all edges u->v with weight w
        for (ull u = 0; u < g.size(); ++u) {
            for (ii e : g[u]) {
                ll v = e.first;
                ll w = e.second;
                // relax the edge
                if (d[u] < INF && d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    changed = true;
                }
            }
        }
    }
    // there is a negative cycle if there were changes in the last iteration
    return changed;
}


// input: weighted directed graph (g[u] contains pairs (v,w) such that u->v has weight w, nodes are named
// 0,1,...,|V|-1). output: the pairwise distances (d). time: O(V^3).
void FloydWarshall(const vvii& g, vvi& d) {
    // initialize distances according to the graph edges
    d.assign(g.size(), vi(g.size(), INF));
    for (ll u = 0; u < g.size(); ++u)
        d[u][u] = 0;
    for (ll u = 0; u < g.size(); ++u)
        for (ii e : g[u]) {
            ll v = e.first;
            ll w = e.second;
            d[u][v] = min(d[u][v], w);
        }
    // relax distances using the Floyd-Warshall algorithm
    for (ll k = 0; k < g.size(); ++k)
        for (ll u = 0; u < g.size(); ++u)
            for (ll v = 0; v < g.size(); ++v)
                d[u][v] = min(d[u][v], d[u][k] + d[k][v]);
}


/********** Min Spanning Tree **********/


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


// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (n), all nodes are between 0 and n-1.
// output: weight of a minimum spanning tree.
// time: O(ElogV).
ll Kruskal(vector<iii>& edges, ll n) {
    sort(edges.begin(), edges.end());
    ll mst_cost = 0;
    UnionFind components(n);
    for (iii e : edges) {
        if (components.find(e.second.first) != components.find(e.second.second)) {
            mst_cost += e.first;
            components.unite(e.second.first, e.second.second);
        }
    }
    return mst_cost;
}


/********** Max Flow **********/


ll augment(vvi& res, ll s, ll t, const vi& p, ll minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    }
    else if (p[t] != -1) {
        ll f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
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
ll EdmondsKarp(ll n, vector<iii>& edges, ll s, ll t) {
    // initialise adjacency list and residuals adjacency matrix
    vvi res(n, vi(n, 0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    ll addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        queue<ll> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            ll u = q.front();
            q.pop();
            if (u == t)
                break;
            for (ll v : adj[u])
                if (res[u][v] > 0 && dist[v] == INF) {
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
