#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>


#include <vector>



using namespace std;

using ll = long long int;


ll powmodn(ll a, ll q, ll n){
    ll res = 1;
    while(q){
        if (q%2) res = (res * a) % n;
        a = (a * a) % n;
        q >>= 1;
    }
    return res;
}

bool MR(ll n, int k=5){
    if(n==1 || n==4)
        return false;
    if(n==2 || n==3)
        return true;
    ll m = n - 1;
    int r = 0;
    while (m%2 == 0){
        m >>= 1;
        r+=1;
    }
    /* !!! Deterministic version for n<2^64 !!! */
//    int dtrm_set[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
//    for(ll a: dtrm_set){
//        if(a >= n) break;
    /* !!! End of deterministic version !!! */

    /* !!! Probablistic version !!! */
    while(k--){
        ll a = rand() % (n-4) + 2;
        /* !!! end of probablisitic version !!! */
        a = powmodn(a,m,n);
        if(a==1) continue;
        int i = r;
        while(i-- && a != n-1){
            a = (a*a)%n;
            if(a == 1) return false;
        }
        if(i == -1) return false;
    }
    return true;
}


int main() {

//    bool first = true;

    ll L, U;

    while (cin >> L >> U)
    {
        vector<ll> P;

        for (int i = L; i <= U; i++)
        {
            if (MR(i)) P.push_back(i);
        }

        if (P.size() < 2) {
            cout << "There are no adjacent primes." << endl;
            continue;
        }

        ll d1;
        ll d2;
        ll ddist = -1;

        ll dist =  1000001;
        ll c1, c2;
        ll psize = P.size();
        for (ll i = 1; i < psize; i++) {
            if (P[i] - P[i - 1] < dist) {
                c1 = P[i - 1];
                c2 = P[i];
                dist = P[i] - P[i - 1];
            }
            if (P[i] - P[i - 1] > ddist) {
                d1 = P[i - 1];
                d2 = P[i];
                ddist = P[i] - P[i - 1];
            }
        }
        cout << c1 << "," << c2 << " are closest, " << d1 << "," << d2 << " are most distant." << endl;
    }
    return 0;

}
