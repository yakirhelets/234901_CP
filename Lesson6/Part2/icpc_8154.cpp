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

int main() {
    unsigned long long n;
    while (cin >> n) {
        vector<unsigned long long> cols(n);
        vector<unsigned long long> rows(n);
        for (int i=0;i<n;i++) {
            int width;
            cin >> width;
            cols[i]=width;
        }
        for (int i=0;i<n;i++) {
            int height;
            cin >> height;
            rows[i]=height;
        }
        vector<unsigned long long> ncols(3,0);
        vector<unsigned long long> nrows(3,0);
        for (int i=0;i<n;i++) {
            if(i%3==0) {
                ncols[0]+=cols[i];
                nrows[0]+=rows[i];
            }
            if(i%3==1) {
                ncols[1]+=cols[i];
                nrows[1]+=rows[i];
            }
            if(i%3==2) {
                ncols[2]+=cols[i];
                nrows[2]+=rows[i];
            }
        }
        cout << nrows[0]*ncols[1]+nrows[1]*ncols[0]+nrows[2]*ncols[2] << " " <<
        nrows[2]*ncols[0]+nrows[0]*ncols[2]+nrows[1]*ncols[1] << " " <<
        nrows[0]*ncols[0]+nrows[2]*ncols[1]+nrows[1]*ncols[2] << endl;
    }
    return 0;
}