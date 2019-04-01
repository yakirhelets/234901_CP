#include <iostream>
#include <unordered_set>
#include <vector>
#include <math.h>
#include <bitset>

using namespace std;
static int wo = 0;

int* calc_wo(int arr[], int size) {
    int* newArr = new int[size/2];
    for (int i = 0 ; i < size ; i+=2) {
        if (arr[i] != arr[i+1]) {
            wo++;
            newArr[i/2] = 1;
        } else {
            newArr[i/2] = arr[i];
        }
    }

    return newArr;
}


int main ()
{
    long long C;

    cin >> C;

    while (C--)
    {

        int n = 0;
        long long m = 0;
        cin >> n;
        cin >> m;
        int p = (int)(pow(2, n));
        int* tournament = new int[p];
        for (int i = 0 ; i<p ; i++) {
            tournament[i] = 1;
        }
        int out;
        for (int i = 0 ; i<m ; i++) {
            cin >> out;
            tournament[out-1] = 0;
        }
        while (p > 1) {
            tournament = calc_wo(tournament, p);
            p=p/2;
        }
        cout << wo << endl;
        wo = 0;


    }
}