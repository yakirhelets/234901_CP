#include <cmath>
#include <iostream>

using namespace std;

int main() {
    int TC;
    cin >> TC;
    string s;
    getline(cin, s);
    while (TC--) {
        getline(cin, s);

        double length = sqrt(s.length());
        if ((double) floor(length) == length) {
            for (int i = 0; i < floor(length); i++) {
                for (int j = 0; j < floor(length); j++) {
                    cout << s[floor(length) * j + i];
                }
            }
            cout << endl;
        } else {
            cout << "INVALID" << endl;
        }
    }
}
