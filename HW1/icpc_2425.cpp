#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>


using namespace std;

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;


/********** Dijkstra **********/

// input: digraph (g), source (s)
// output: distances from s (dist)
void Dijkstra(const vector<vii>& g, int s, vi& dist) {
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


int main() {

    int TC = 0;
    cin >> TC;
    while (TC--) {
        int N, E, T, M;
        cin >> N >> E >> T >> M;
        // Preparing a reversed maze graph
        vvii maze = vvii(N);
        while (M--) {
            int entry, exit, time;
            cin >> entry >> exit >> time;
            maze[exit-1].push_back(make_pair(entry-1, time));
        }
        vi distances = vi(N);
        Dijkstra(maze, E-1, distances);
        int lowerThanE = 0;
        for (int i : distances) {
            if (i <= T) {
                lowerThanE++;
            }
        }
        cout << lowerThanE << endl;
        if (TC) {
            cout << endl;
        }
    }

}
