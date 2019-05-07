#include <algorithm>
#include <cassert>
#include <cmath>
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

const int N = 1e5;  // limit for array size
int n;  // array size
int t[2 * N];

void build() {  // build the tree

    for (int i = 0 ; i<2*N ; i++) {
        t[i] = 1;
    }
    for (int i = n - 1; i > 0; --i)
        t[i] = t[i<<1] * t[i<<1|1];
}

void modify(int p, int value) {  // set value at position p
    for (t[p += n] = value; p > 1; p >>= 1)
        t[p>>1] = t[p] * t[p^1];
}

int query(int l, int r) {  // sum on interval [l, r)
    int res = 1;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1)
            res *= t[l++];
        if (r&1)
            res *= t[--r];
    }
    return res;
}

int getSign(int num) {
    if (num > 0) {
        return 1;
    } else {
        if (num < 0) {
            return -1;
        } else {
            return 0;
        }
    }
}

int main() {
    int N, K;
    while(cin >> N >> K) {
        n =N;
        build();
        // creating a vector representing the sign of the numbers
        for (int i=0 ; i<N ; i++) {
            int num;
            cin >> num;
            modify(i, getSign(num));
        }
        while(K--) {
            string command;
            int num1, num2;
            cin >> command >> num1 >> num2;
            if (command=="C") {
                modify(num1-1, getSign(num2));
            } else {
                int res = query(num1-1, num2);
                if (res==0) {
                    cout << "0";
                } else {
                    cout << (res>0?"+":"-");
                }
            }
        }
        cout << endl;
    }

    return 0;
}

