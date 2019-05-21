#include <iostream>
#include <vector>

using namespace std;
using vi = vector<int>;

int main() {
    int m, n;
    char ch_s, ch_e;
    string str;

    while (cin >> str && str != ".") {
        vi ends;
        bool found = true;
        m = str.size();
        n = 0;

        ch_s = str[0];
        ch_e = str[m - 1];

        for (int i = 0; i < m; i++)
            if (str[i] == ch_e)
                ends.push_back(i);

        int e_size = ends.size();
        for (int e_idx = 0; e_idx < e_size; e_idx++) {
            int s = 0;
            int e = ends[e_idx];
            int sub_len = e - s + 1;
            found = true;

            n = m / sub_len;
            int s_idx = 0;
            for (int i = 1; i < n; i++) {
                for (int sub_idx = 0; sub_idx < sub_len; sub_idx++) {
                    if (str[s_idx++] != str[sub_idx]) {
                        found = false;
                        break;
                    }
                }
                if (!found)
                    break;
            }

            if (found) {
                cout << n << "\n";
                break;
            }
        }
    }
    return 0;
}
