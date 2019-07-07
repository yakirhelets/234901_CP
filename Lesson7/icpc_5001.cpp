#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;

int main() {
    vector<ll> res;
    for (int i = 0; i < 3; i++) {
        res.push_back(1);
    }

    for (int i = 0; i < 70; i++) {
        res.push_back(res[i] + res[i + 1] + res[i + 2]);
    }

    int n, i = 1;
    while (cin >> n) {
        if (n == 0) {
            break;
        }

        cout << "Case " << i++ << ": " << res[n - 1] << endl;
    }
}
