#include <iostream>
#include <string>

using namespace std;

bool f(string str, int start) {
    string sub_str;
    bool res = false;
    int cnt = 1;
    int str_size = str.size();

    if (str_size == 0)
        return true;
    else if (str_size == 1)
        return false;

    for (int i = start + 1; i < str_size; i++) {
        if (str[i] == str[i - 1])
            cnt++;
        else {
            if (cnt >= 2) {
                sub_str = str;
                sub_str.erase(i - cnt, cnt);
                res |= f(sub_str, 0);
                res |= f(str, i);
                return res;
            }
            cnt = 1;
        }
    }
    if (cnt == str_size)
        return true;
    return res;
}

int main() {
    int T;
    string str;
    cin >> T;

    while (T--) {
        cin >> str;
        cout << (int)f(str, 0) << "\n";
    }

    return 0;
}