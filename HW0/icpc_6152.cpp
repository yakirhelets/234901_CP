#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int main() {
    int S_ones;
    int T_ones;
    int res;
    int TC;
    int tc = 0;
    string S;
    string T;
    scanf("%d", &TC);
    while (TC--) {
        cin >> S;
        cin >> T;
        res = 0;
        string Xor;
        S_ones = (int) count(S.begin(), S.end(), '1');
        T_ones = (int) count(T.begin(), T.end(), '1');
        // iterate over the "?" in S and swap them in order to equalize S_ones, T_ones
        if (S_ones > T_ones) {
            res = -1;
        } else {
            for (int i = 0 ; i < S.length() ; i++) {
                if (S[i] == '?') {
                    if (T[i] == '1' && (T_ones-S_ones > 0)) {
                        S[i] = '1';
                        S_ones++;
                        res++;
                    } else {
                        S[i] = '0';
                        res++;
                    }
                }
            }
            for (int i = 0 ; i < S.length() ; i++) {
                if (S[i] == '0' && T[i] == '1' && (T_ones-S_ones > 0)) {
                    S[i] = '1';
                    S_ones++;
                    res++;
                }
                Xor.push_back((S[i]-'0')^(T[i]-'0')+'0');
            }
            int num_swaps = (int) count(Xor.begin(), Xor.end(), '1');
            res += num_swaps/2 + num_swaps%2;


        }
        cout << "Case " << to_string(++tc) << ": " << res << endl;
    }
    return 0;
}