#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;

bool isValidSolution(vector<int> v, int sol, int box_num) {
    int i=0;
    while(box_num) {
        v[i]-=sol;
        if (v[i] <= 0) {
            i = (i+1)%v.size();
            if (i == 0) {
                break;
            }
        }
        box_num--;
    }
    if (box_num>0) {
        return true;
    } else {
        return (v[i] <=0);
    }

}

int binarySearch (vector<int> vec, int box_num, int low, int high) {
    int sol = ((high+low)/2);
    if (low >= high) {
        return sol;
    }

    vector<int> v(vec);
    if (isValidSolution(v, sol, box_num)) {
        return binarySearch(vec, box_num, low, sol);
    } else {
        return binarySearch(vec, box_num, sol+1, high);
    }
}

int main ()
{
    int cities;
    int boxes;

    while (true)
    {
        cin >> cities;
        cin >> boxes;

        int pop;

        if (cities == -1) break;
        vector<int> q(0);


        //boxes -= cities;
        int high = 0;
        int low = 1;
        while (cities--)
        {
            cin >> pop;
            if (pop > high) {
                high = pop;
            }
            q.push_back(pop);
        }
        int sol = binarySearch(q, boxes, low, high);
        cout << sol << endl;
    }
    return 0;
}
