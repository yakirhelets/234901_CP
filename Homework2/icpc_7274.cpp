#include <iostream>
#include <vector>
#include <queue>

using namespace std;
using ll = long long int;

int main ()
{
    ll T, N, canvsize;

    while (cin >> T)
    {
        while (T--)
        {
            priority_queue<ll, vector<ll>, greater<ll>> minheap;
            cin >> N;

            while (N--)
            {
                cin >> canvsize;
                minheap.push(canvsize);
            }

            ll amount = 0;

            // painting is complete when the merge sort is done => 1 array is made
            while (minheap.size() > 1)
            {
                ll left, right;
                left = minheap.top(); minheap.pop();
                right = minheap.top(); minheap.pop();
                amount += left + right;
                minheap.push(left + right);
            }
            cout << amount << "\n";
        }
    }
    return 0;
}