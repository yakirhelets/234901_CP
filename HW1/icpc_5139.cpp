#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <map>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vi visited(26,0);

void dfs(const vvi& g, int u, vi& output) {
    visited[u] = 1;

    for (int i = 0; i < (int) g[u].size(); i++) {
        int v = g[u][i];
        if (!visited[v]) {
            dfs(g, v, output);
        }
    }

    output.push_back(u);
}


int main()
{
    string word;
    vector<string> sorted;
    while(cin >> word) {
        if (word != "#") {
            sorted.push_back(word);
        } else {
            if (sorted.size() == 1) {
                cout << sorted[0] << endl;
                break;
            }
            vvi letters(26, vi());
            vi found(26, 0);
            for (int i=1 ; i<sorted.size() ; i++) {
                for (int j=0 ; j<sorted[i].length() && j < sorted[i-1].length(); j++) {
                    if (sorted[i-1].at(j) != sorted[i].at(j)) {
                        found[sorted[i-1].at(j) - 'A'] = 1;
                        found[sorted[i].at(j) - 'A'] = 1;
                        letters[sorted[i-1].at(j) - 'A'].push_back(sorted[i].at(j) - 'A');
                        break;
                    }
                }
            }


            vi output;
            for (int i=0 ; i< letters.size() ; i++) {
                if (visited[i]==0 && found[i] == 1) {
                    dfs(letters, i, output);
                }
            }
            for (int i = output.size() - 1; i >= 0; i--) {
                cout << (char)(output[i] + 'A');
            }
            cout << endl;
            sorted.clear();
            visited = vi(26,0);

        }

    }


    return 0;
}