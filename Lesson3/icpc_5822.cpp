#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;
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
        vector< tuple<int, int, int> > q(cities);


        boxes -= cities;
        while (cities--)
        {
            cin >> pop;

            q.push_back(tuple<int, int, int>(pop, 1, pop));
        }

        make_heap(q.begin(), q.end());

        while (boxes--)
        {
             tuple<int, int, int> max = q.front();
             std::pop_heap (q.begin(),q.end()); 
             q.pop_back();

             tuple<int, int, int> tmp(get<2>(max) / (get<1>(max) + 1), (get<1>(max) + 1), (get<2>(max)));
             q.push_back(tmp); std::push_heap (q.begin(),q.end());
        }

        cout << get<0>(q.front()) << endl;

    }
    return 0;
}
