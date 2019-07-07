#include <iostream>
#include <vector>
#include <bitset>

using namespace std;
char values[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
bool isInnerSpace() {

}

int countInnerSpaces() {
    int count=0;
    if (isInnerSpace()) {
        count++;
    }
    return count;
}

void HexaToMatrix(vector<vector<int>>& grid, int row, int W, string str) {
    string binary;
    for (char c : str) {
        for (int i = 0; i < 16; i++) {
            if (c == values[i]) {
                binary += (to_string(i));
            }
        }
    }
    for (int i = 0; i < W; i++) {
        grid[row][i] = stoi(to_string(binary.at(i)));
    }
}

int main() {
    int H,W;
    while (cin >> H >> W, (H!=0 && W!=0)) {
        vector<vector<int>> grid(H);
        for (int i=0 ; i<H ; i++) {
            string row;
            cin >> row;
            grid[i] = vector<int>(W);
            HexaToMatrix(grid, i, W, row);
        }
    }
    return 0;
}