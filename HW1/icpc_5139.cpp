#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <map>

using namespace std;

typedef pair<int,int> ii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

int dfs(const vvi& g, int s, vi& output) {
    int count=0;
    stack<int> q;
    q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    while (!q.empty()) {
        int u = q.top();
        q.pop();
        count++;
        output.push_back(u);
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                q.push(v);
            }
    }
    return count;
}
/*
 * Input graphs should be represented as an adjacency list
 * where the nodes are named 0,1,...,|V|-1.
 * If g is unweighted (type vvi), g[u] contains the neighbors of u
 * If g is weighted (type vvii), g[u] contains pairs (v,w) such that u->v has weight w
 */

/********** topological sort **********/

// input: a graph (g)
// output: is g a DAG (return value), a topological ordering of g (order)
// comment: order is valid only if g is a DAG
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
                return 0;
            }

            map<int, char> toLetter;
            map<char, int> toIndex;

            vvi letters;

            int count = 0;
            for (int i=0 ; i<sorted.size()-1 ; i++) {
                for (int j=0 ; j<min(sorted[i].size(), sorted[i+1].size()) ; j++) {
                    if (sorted[i][j] != sorted[i+1][j]) {
                        if (toIndex.find(sorted[i][j]) == toIndex.end()) {
                            toIndex.insert(make_pair(sorted[i][j], count));
                            toLetter.insert(make_pair(count, sorted[i][j]));
                            vi letter;
                            letters.push_back(letter);
                            count++;
                        }
                        if (toIndex.find(sorted[i+1][j]) == toIndex.end()) {
                            toIndex.insert(make_pair(sorted[i+1][j], count));
                            toLetter.insert(make_pair(count, sorted[i+1][j]));
                            vi letter;
                            letters.push_back(letter);
                            count++;
                        }
                        letters[toIndex.at(sorted[i][j])].push_back(toIndex.at(sorted[i+1][j]));
                        break;
                    }
                }
            }

            vi order;
            vi output;
            topological_sort(letters, order);
            for (int i=0 ; i< order.size() ; i++) {
                if (dfs(letters, i, output) == letters.size()) {
                    for (int j=0 ; j< output.size() ; j++) {
                        cout << toLetter.at(output[j]);
                    }
                    cout << endl;
                    sorted.clear();
                    break;
                } else {
                    output.clear();
                }
            }


        }
    }


    return 0;
}