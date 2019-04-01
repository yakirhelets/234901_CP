#include <iostream>
#include <stdlib.h>

using namespace std;

int main() {
    int W;
    int N;
    int area = 0;
    int wi = 0;
    int li = 0;
    while (cin >> W) {
        cin >> N;
        while (N--) {
            cin >> wi;
            cin >> li;
            area += wi*li;
        }
        cout << area/W << endl;
        area = 0;
    }
    return 0;
}