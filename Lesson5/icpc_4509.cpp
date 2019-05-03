#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <list>
#include <set>
#include <tuple>
#include <vector>
#include <queue>


using namespace std;

using ll = long long;
using ull = unsigned long long;
using sz = size_t;

// This file contains implementations of some well-known graph algorithms.
// Written by Nofar Carmeli.
// Some code is based on the book Competitive Programming 3 by Steven and Felix Halim.

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef tuple<int, int, int> iii;

const int INF = 1e9;


/********** Bellman-Ford **********/

// input: weighted directed graph (g), source node (s)
// output: is there a negative cycle in g? (return value), the distances from s (d)
// comment: the values in d are valid only if there is no negative cycle
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

/// XXXXX - Name
int main() {
    int W, H, G, E;

    while (cin >> W >> H && W != 0 && H != 0)
    {
        vvii graveyard = vvii(H*W);
        int G;
        int weights[H][W] = {0};
        for (int i = 0 ; i < H ; i++) {
            std::fill_n(weights[i], W, 1);
        }
        cin >> G;
        while (G--)
        {
            int x,y;
            cin >> x >> y;
            weights[y][x] = INF;
        }

        cin >> E;
        while (E--)
        {
            int x1, y1, x2,y2,w;
            cin >> x1 >> y1 >> x2 >> y2 >> w;
            weights[y1][x1] = 0;
            vii hole = vii();
            hole.push_back(make_pair(y2*W+x2, w));
            graveyard[y1*W+x1] = hole;
        }

        for (int i =0 ; i < W; i++) // x axis
        {
            //v.clear();
            for (int j =0 ; j < H; j++) // y axis
            {
                vii v = vii();
                if (j == H-1 && i == W-1) {
                    graveyard[j*W+i] = v;
                    break;
                }
                if (weights[j][i] == 1) {
                    if(i>0) {
                        v.push_back(make_pair(j*W+(i-1), weights[j][i-1]==0?1:weights[j][i-1]));
                    }
                    if (j>0) {
                        v.push_back(make_pair((j-1)*W+i, weights[j-1][i]==0?1:weights[j-1][i]));
                    }
                    if(i<W-1) {
                        v.push_back(make_pair(j*W+(i+1), weights[j][i+1]==0?1:weights[j][i+1]));
                    }
                    if (j<H-1) {
                        v.push_back(make_pair((j+1)*W+i, weights[j+1][i]==0?1:weights[j+1][i]));
                    }
                    graveyard[j*W+i] = v;
                }

            }
        }
        vi path = vi(W*H);
        bool res = BellmanFord(graveyard, 0, path);

        if (!res) {
            int t = path[path.size()-1];
            if (t == INF) {
                cout << "Impossible" << endl;
            } else {
                cout << t << endl;
            }
        } else {
            cout << "Never" << endl;
        }
    }
    return 0;
}
