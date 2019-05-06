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

bool isValidSolution(int* sol, int row, int col) {
    vector<pair<int, int>> tuples;
    tuples.push_back(make_pair(col, row));
    int flag = 1;
    for (int i = 0 ; i < 7; i++) {
        if (i+1 == col) {
            flag++;
        }
        tuples.push_back(make_pair(i+flag, sol[i]));
    }
    for (int i = 0 ; i < 8; i++) {
        for (int j = i+1 ; j <8 ; j++) {
            if (abs(tuples[i].first-tuples[j].first) == abs(tuples[i].second-tuples[j].second)) {
                return false;
            }
        }

    }
    return true;
}

int main() {
    int TC;
    cin >> TC;
    while(TC--) {
        int row, col;
        cin >> row >> col;
        int perm[7];
        cout << "SOLN       COLUMN" << endl << " #      1 2 3 4 5 6 7 8" << endl << endl;
        int row_to_add = 1; // current row number to add
        for (int i=0 ; i<7; i++) { // iterating over columns
            if (row_to_add == row) {
                perm[i] = ++row_to_add;
                row_to_add++;
            } else {
                perm[i] = row_to_add++;
            }
        }
        int solutionNum = 1;
        do {
            // Printing the current permutation
            if (isValidSolution(perm, row, col)) {
                cout << ((solutionNum>9)?"":" ") << solutionNum << "     ";

                int flag = 1;
                for (int i = 0 ; i < 7; i++) {
                    if (i+1 == col) {
                        flag++;
                        cout << " " << row;
                    }
                    cout << " " << perm[i];
                }
                if (flag == 1) {
                    cout << " " << row;
                }
                cout << endl;
                solutionNum++;
            }

        } while ( std::next_permutation(perm, perm+7));

        if (TC!=0)
            cout << endl;

    }

    return 0;
}

