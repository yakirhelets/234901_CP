// Center of symmetry
#include <cstdio>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

typedef long long ll;

bool comparePoints(pair<ll, ll>& a, pair<ll, ll>& b)
{
    return a.first != b.first ? a.first < b.first : a.second < b.second;
}

int main()
{
    ll TC, n, x, y;
    cin >> TC;
    while (TC--) {
       cin >> n;
       vector<pair<ll, ll>> coordinates(n);
       for (int i=0 ; i<n ; i++) {
           cin >> x >> y;
           coordinates[i] = make_pair(x, y);
       }
       sort(coordinates.begin(), coordinates.end(), comparePoints);
       pair<double, double> center = make_pair((coordinates[0].first+coordinates[n-1].first)/2.0,
               (coordinates[0].second+coordinates[n-1].second)/2.0);
       bool notCenter = false;
       for (int i=1 ; i<=n/2 ; i++) {
           if (coordinates[i].first-center.first != center.first-coordinates[n-1-i].first ||
                   coordinates[i].second-center.second != center.second-coordinates[n-1-i].second) {
               cout << "no" << endl;
               notCenter = true;
               break;
           }
       }
       if (!notCenter) {
           cout << "yes" << endl;
       }
    }
    return 0;
}

