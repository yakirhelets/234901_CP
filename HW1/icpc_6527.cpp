#include <cstdio>
#include <cmath>
#include <iostream>


using namespace std;

typedef long long ll;
const int maxt = 54;


ll calc(ll num)
{
    ll ret = 0, cnt = 0;
    for(ll i = maxt; i >= 0; --i)
        if(num & (1ll << i))
        {
            ret += cnt * (1ll << i);
            if(i)
                ret += i * (1ll << i - 1);
            ++cnt;
        }
    return ret;
}


int main()
{
    ll low, high;
    while(cin >> low >> high) {
        cout << calc(3) << endl;
        printf("%lld\n", calc(high + 1) - calc(low));
    }
    return 0;
}