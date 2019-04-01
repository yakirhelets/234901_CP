#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;
int main() {

    int tc = 0;
    bool res;
    int x;
    while (scanf("%d", &x) != EOF) {
        res = false;
        int angle = 0;
        for (int m = 0 ; m<720 ; m++) {
            if (x == angle) {
                res = true;
                break;
            } else {
                angle+=6;
                if (m%12 ==0) {
                    angle-=6;
                }
            }

        }
        cout << (res?"Y\n":"N\n");
    }
    return 0;
}