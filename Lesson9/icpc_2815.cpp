#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> visited;

int solve(vector<vector<int>>& blocks, int l, int m) {
    if (visited[l][m] != -1) {
        return visited[l][m];
    }
    if (m == 1 && l == 1) {
        return visited[l][m] = blocks[l][m];
    }
    if (m == 1) {
        return visited[l][m] = blocks[l][m] + solve(blocks, l - 1, m);
    }
    if (l == 1) {
        return visited[l][m] = blocks[l][m] + solve(blocks, l, m - 1);
    }
    return visited[l][m] = blocks[l][m] + max(solve(blocks, l, m - 1), solve(blocks, l - 1, m));
}


int main() {
    int n;
    int max_range = 101;
    while (cin >> n && n != 0) {
        vector<vector<int>> blocks(max_range, vector<int>(max_range, 0));
        for (int i = 0; i < n; ++i) {
            int l, m;
            cin >> l >> m;
            blocks[l][m]++;
        }
        visited = vector<vector<int>>(max_range, vector<int>(max_range, -1));
        int res = solve(blocks, max_range-1, max_range-1);
        cout << res << endl;
    }
    cout << "*" << endl;
}
