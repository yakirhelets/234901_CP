#include <cstdio>
#include <cmath>
#include <iostream>


using namespace std;

typedef long long LL;
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

long long pop_accumulation_bit(long long x) {
    if (x == 0)return 0;
    long long r = 1;
    int i;
    for (i = 0; x >> (i + 1); i++){
        r = r * 2 + (1LL << i) - 1;
    }
    return r + proc(~(1LL << i)&x) + (x - (1LL << i));
}

int main()
{
    ll low, high;
    while(cin >> low >> high) {
        cout << (calc(high + 1) - calc(low)) << endl;
    }
    return 0;
}