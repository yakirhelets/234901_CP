#include <iostream>
#include <stdlib.h>
#include <algorithm>

using namespace std;
int main() {

    bool res;
    string line;
    string done = "DONE";

    while (getline(cin, line)) {
        if (line == done) {
            return 0;
        } else {
            res = true;
            int i = 0;
            int j = line.length()-1;
            while (i <= j) {
                while (line[i] == '.' || line[i] == ',' || line[i] == '?' || line[i] == '!'|| line[i] == ' ') {
                    i++;
                }
                while (line[j] == '.' || line[j] == ',' || line[j] == '?' || line[j] == '!'|| line[j] == ' ') {
                    j--;
                }
                if (tolower(line[i]) != tolower(line[j])) {
                    res = false;
                    break;
                }
                i++;
                j--;
                if (res ==false) {
                    break;
                }
            }

            cout << (res?"You won't be eaten!\n":"Uh oh..\n");
        }

    }
    return 0;
}