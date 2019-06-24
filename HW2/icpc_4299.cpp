#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

using ii = pair<int, int>;
using vi = vector<int>;
using vvi = vector<vi>;
using vii = vector<ii>;
using vvii = vector<vii>;

const int INF = 1e9;

/********** Floyd-Warshall **********/

// input: weighted directed graph (g)
// output: the pairwise distances (d)
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


#define NR_CITIES 100
#define MAX_M 10000

int main ()
{
    int T, N, R, C, a, b, m, c = 1;
    double p;
    cin >> T;

    while (T--)
    {
        cin >> N >> R;
        p = 1.0 / R;
        vvii g(N, vii());
        double dp[NR_CITIES+1][MAX_M+1] = {0.0};

        // build the graph from input
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
            {
                char chr;
                cin >> chr;
                if (chr == 'Y') g[i].emplace_back(j, 1);
            }

        // dp[n][m] - the probabiliy to afford a trip through n-long path with a budget m.
        
        dp[0][0] = 1.0; // base: staying put, with no budget.

        // max length of a path is the number of cities
        for (int path_len = 1; path_len <= NR_CITIES; path_len++)
            for (int weight = 1; weight <= R; weight++) // for each possible weight of the last edge on path
                for (int budget = weight; budget <= NR_CITIES * R; budget++) // for every possible budget
                    dp[path_len][budget] += dp[path_len-1][budget - weight] * p;

        
        // find shortest path in graph
        vvi d;
        FloydWarshall(g, d);

        cin >> C;
        cout << fixed << setprecision(6);
        cout << "Case " << c++ << "\n";
        while (C--)
        {
            double total_prob = 0.0;
            cin >> a >> b >> m;
            for (int i = 0; i <= m; i++)
                total_prob += dp[d[a-1][b-1]][i];
            cout << total_prob << "\n";
        }
        cout << "\n";
    }
    return 0;
}