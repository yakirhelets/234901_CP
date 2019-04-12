#include <iostream>
#include <vector>
#include <cmath>
#include <tuple>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;

double radius(double x, double d)
{
    return sqrt(abs(d*d - x*x));
}


int main ()
{
    int i_case = 1;
    while (true) {
        int n, d;
        set<tuple<double, int, int> > points;
        map<tuple<double, int, int>, tuple<double, int, int> > l2r;
        cin >> n;
        cin >> d;
        bool should_break = false;

        if (n == 0 && d == 0) break;

        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x;
            cin >> y;
            if (y > d) {
                should_break = true;
                continue;
            }

            tuple<double, int, int> l = make_tuple(x - radius(y, d), 0, i);
            tuple<double, int, int> r = make_tuple(x + radius(y, d), 1, i);
            points.insert(l);
            points.insert(r);
            l2r.insert(make_pair(l, r));
        }

        if (should_break) {
            cout << "Case " << i_case++ << ": " << -1 << endl;
        } else {

            int counter = 0;
            vector<tuple<double, int, int> > q;

            while (!points.empty()) {
                for (auto it = points.begin(); it != points.end(); it++) {
                    if (get<1>(*it) == 0) {
                        q.push_back(*it);
                        continue;
                    } else {
                        for (auto left = q.begin(); left != q.end(); left++) {
                            points.erase(*left);
                            points.erase(l2r[*left]);
                        }
                        counter++;
                        q.clear();
                        break;
                    }
                }
            }
            cout << "Case " << i_case++ << ": " << counter << endl;
        }
    }

    return 0;
}