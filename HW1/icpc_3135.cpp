#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
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

typedef tuple<int, int, int> tu;

// Comparator between two pairs
class PairCompare
{
public:
    int operator() (const tu& p1, const tu& p2)
    {
        return get<0>(p1) == get<0>(p2) ? get<1>(p1) > get<1>(p2) : get<0>(p1) > get<0>(p2);
    }
};

int main() {

    string inst;
    priority_queue<tu, vector<tu>, PairCompare> instructions; // A min heap sorted by the comparator
    while(cin >> inst && inst != "#") {
        int q_num, interval;
        cin >> q_num >> interval;
        instructions.push(make_tuple(interval, q_num, interval)); // Sorted by the interval
    }
    int n = 0;
    cin >> n;
    for (int i=1 ; i<=n ; i++) {
        // Print the earliest query
        tu top = instructions.top();
        cout << get<1>(top) << endl;
        instructions.pop();
        // Prepare the query for the next interval and add it to the heap
        instructions.push(make_tuple(get<0>(top)+get<2>(top), get<1>(top), get<2>(top)));
    }
    return 0;
}