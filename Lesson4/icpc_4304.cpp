#include <cassert>
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    ll rem;
    while (b > 0) {
        rem = a % b;
        a = b;
        b = rem;
    }
    return a;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        int c;
        cin >> c;
        int gcd_sums = 0;
        ll a1,a2,a3,a4,a5,a6,a7,a8,a9,a10;
        ll sum = 0;
        int max = 0;
        while (c--) {

            scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld", &a1,&a2,&a3,&a4,&a5,&a6,&a7,&a8,&a9,&a10);
            sum = a1+a2+a3+a4+a5+a6+a7+a8+a9-a10;
            if (a10 > max) max = a10;
            if (gcd_sums != 1) {
                gcd_sums = gcd(sum, gcd_sums);

            }

        }
        if (gcd_sums <= 1  || gcd_sums <= max) {
            cout << "impossible" << endl;
        } else {
            cout << to_string(gcd_sums) << endl;
        }
    }
    return 0;
}
