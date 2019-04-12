#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;
int main ()
{
    int TC;
    cin >> TC;
    while(TC--) {
        int database_size;
        cin >> database_size;
        vector<tuple<string, int, int>>database(database_size);
        for (int i=0 ; i<database_size ; i++) {
            string car;
            int l;
            int h;
            cin >> car;
            cin >> l;
            cin >> h;
            tuple<string, int, int> database_line = make_tuple(car, l, h);
            database[i] = database_line;
        }
        int query_num;
        cin >> query_num;
        while (query_num--) {
            int price;
            cin >> price;
            vector<string> found_cars;
            for (int j=0 ; j<database_size ; j++) {
                int low = get<1>(database[j]);
                int high = get<2>(database[j]);
                if (price >= low && price <= high) {
                    found_cars.push_back(get<0>(database[j]));
                    if (found_cars.size() > 1) {
                        break;
                    }
                }
            }
            if (found_cars.size() == 1) {
                cout << found_cars.at(0) << endl;
                found_cars.clear();
            } else {
                cout << "UNDETERMINED" << endl;
            }
        }
        if (TC) {
            cout << endl;
        }
    }
    return 0;
}
