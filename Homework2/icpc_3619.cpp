#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

using vi = vector<int>;
using vb = vector<bool>;

/* ASSETS */
#define MAX_N 1120
#define MAX_K 14

vi primes;
int dp[MAX_N+1][MAX_K+1];

void make_primes()
{
    vb ps(MAX_N + 1, true);
    ps[0] = false;
    ps[1] = false;
    int sqrtn = sqrt(MAX_N);
    for (int i = 0; i <= sqrtn; ++i) {
        if(ps[i]){
            for (int j = i*i; j <= MAX_N; j+=i) {
                ps[j] = false;
            }
        }
    }

    for (int i = 2; i < MAX_N; i++)
        if (ps[i]) primes.push_back(i);
}


int main()
{
    int n, k;
    make_primes();

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