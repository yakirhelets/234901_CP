#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
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

static vector<int> amounts;

struct cmp {
    bool operator()(int a, int b) {
        return amounts[a] > amounts[b] || (amounts[a] == amounts[b] && a < b);
    }
};


int main() {
    int TC;
    cin >> TC;
    while(TC--) {
        int price, n;
        cin >> price >> n;
        amounts = vector<int>(n);
        vector<int> indexes(n, 0); // meant for sorting
        vector<int> payed(n, 0);
        int sum=0;
        for (int i=0 ; i<n ; i++) {
            int amount;
            cin >> amount;
            amounts[i] = amount;
            sum+=amount;
            indexes[i]=i;
        }
        if (sum < price) {
            cout << "IMPOSSIBLE" << endl;
            continue;
        }

        int div;
        int rem;

        while (price>0) {
            // sorting the payers as defined in the problem
            sort(indexes.begin(), indexes.begin()+n, cmp());

            // go to the first payer that has the least to spare
            int first_payer = n;
            while(first_payer--)
                if(amounts[indexes[first_payer]] > 0)
                    break;

            div = amounts[indexes[first_payer]];
            int temp_payed = div*(++first_payer); // how much can be payed so far equally
            rem = 0;

            // we're sparing too much money
            if(temp_payed>price) {
                temp_payed=price;
                div = price/first_payer;
                rem = price%first_payer;
            }

            // dividing the payment and remainder among the other payers according to the order
            for(int i = 0; i < first_payer; ++i){
                int x = indexes[i];
                if(amounts[x] > 0){
                    payed[x] += div;
                    amounts[x] -= div;
                    // dividing the remainder
                    if(rem>0 && amounts[x]>0) {
                        payed[x]++;
                        amounts[x]--;
                        rem--;
                    }
                }
            }
            price -= temp_payed;
        }
        for (int i=0 ; i<n-1 ; i++) {
            cout << payed[i] << " ";
        }
        cout << payed[n-1] << endl;
    }

    return 0;
}