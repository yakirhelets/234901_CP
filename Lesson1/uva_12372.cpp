#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;
int main() {

    int tc = 0;
    bool res;
    int x;
    int y;
    int z;
    int TC;
    scanf("%d", &TC);
    while (TC--) {
        scanf("%d %d %d", &x, &y, &z);
        res =  (x<=20 && y<=20 && z<=20);
        cout << "Case " + to_string(++tc) + ": " + (res?"good":"bad") +"\n";
    }
    return 0;
}