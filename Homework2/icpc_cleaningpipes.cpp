#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using vi = vector<int>;
using vb = vector<bool>;

/* ASSETS */
#define MAX_N 1120
#define MAX_K 14



int main()
{
    int wells, pipes;
    while (cin >> wells >> pipes) {
        // Wells
        vector<int> wells_x;
        vector<int> wells_y;
        for (int i=0 ; i<wells ; i++) {
            // wells are numbered 1...w
            int x;
            cin >> x;
            int y;
            cin >> y;
            wells_x.push_back(x);
            wells_y.push_back(y);
        }
        // Pipes
        vector<int> pipes_w;
        vector<int> pipes_x;
        vector<int> pipes_y;
        for (int i=0 ; i<wells ; i++) {
            // wells are numbered 1...w
            int w;
            cin >> w;
            int x;
            cin >> x;
            int y;
            cin >> y;
            pipes_w.push_back(w);
            pipes_x.push_back(x);
            pipes_y.push_back(y);
        }
    }

    int n, k;

    // dp[n][k] = number of sets of *k* different primes which sum up to *n*
    dp[0][0] = 1; // base - only empty set sums up to zero
    for (int prime : primes)
        for (int i = MAX_N; i >= 1; i--)
            if (prime <= i)
                for (int j = MAX_K; j >= 1; j--)
                    dp[i][j] += dp[i - prime][j - 1]; // recursion rule

    while (cin >> n >> k && !(n == 0 && k == 0))
        cout << dp[n][k] << "\n";

    return 0;
}