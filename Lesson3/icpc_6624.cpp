#include<iostream>
#include<cstdio>
#include<utility>
#include<algorithm>
#include<cstring>
#include <iomanip>

using namespace std;

#define MAX_LEN 1100


double calc_probs(int m, const int *card_values) {
    double probs[m+11];

    for (int i = 0; i < 10; i++)
        probs[i] = 1. / 10.;
    for (int i = 10; i <= m; i++)
        probs[i] = 0.;

    for (int i = 0; i <= m; i++) {
        for (int j = 2; j < 12; j++) {
            if (i < j) {
                break;
            }
            if (card_values[i - j] == 0) { //unknown card
                double card_prob = j==10? (4./13.) : (1./13.);
                probs[i] += probs[i - j] * card_prob;
            } else {
                if (card_values[i - j] == j) //known card
                    probs[i] += probs[i - j];
            }
        }
    }
    return probs[m];
}

int main() {
    int n = 0;
    int m = 0;
    while(scanf("%d %d", &n, &m) != EOF) {
        m--;
        int card_values[MAX_LEN] = {0};
        string card;

        for(int i=0; i<n; i++) {
            cin >> card;
            if(card == "10" || card == "J" || card == "Q" || card == "K") {
                card_values[m] = 10;
            } else {
                if(card[0] == 'A') {
                    card_values[m] = 11;
                } else {
                    card_values[m] = card[0] - '0';
                }
            }
            if(i < n-1) {
                m += card_values[m];
            }
        }

        double res = calc_probs(m, card_values);

        cout << setprecision(8) << res << endl;
    }
    return 0;
}