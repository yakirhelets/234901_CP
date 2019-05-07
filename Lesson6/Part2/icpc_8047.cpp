#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;
using ll = long long int;
using ii = pair<ll,ll>;
using vi = vector<ll>;
using vii = vector<ii>;
using vvi = vector<vi>;
using si = set<ll>;

const ll INF = 1e9;

void bfs(const vvi &g, ll s, vector<ll> &d) {
    queue<ll> q;
    q.push(s);
    vector<bool> visible(g.size(), false);
    visible[s] = true;
    d.assign(g.size(), INF);
    d[s] = 0;
    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (ll v : g[u]) {
            if (!visible[v]) {
                visible[v] = true;
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
}

int main ()
{
    ll m, n;
    char l, r;
     
    while (cin >> m >> n)
    {
        vvi g(26, vi());

        while (m--)
        {
            cin >> l >> r;
            g[(ll)(l - 'a')].push_back((ll)(r - 'a'));
        }

        vvi paths(26, vi(26));

        for (int c = 0; c < 26; c++)
        {
            bfs(g, c, paths[c]);
        }

        
        while (n--)
        {
            bool continue_while = false;
            string left, right;
            cin >> left >> right;

            if (left.size() != right.size())
            {
                cout << "no" << "\n";
                continue;
            }

            for (int i = 0; i < left.size(); i++)
            {
                if (paths[(ll)(left[i] - 'a')][(ll)(right[i] - 'a')] == INF)
                {
                    cout << "no" << "\n";
                    continue_while = true;
                    break;
                }
            }

            if (continue_while) continue;
            cout << "yes" << "\n";
        }
    }
    return 0;
}