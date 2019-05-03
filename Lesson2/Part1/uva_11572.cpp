#include <iostream>
#include <unordered_set>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main ()
{
    int TC;
    cin >> TC;
    while (TC--)
    {
        int N;
        cin >> N;

        vector<int> snowSeq = vector<int>(N);
        for (int i=0 ; i<N ; i++) {
            cin >> snowSeq[i];
        }

        map<int,int> position = map<int,int>();
        vector<pair<int,int>> byStart = vector<pair<int,int>>(N);
        vector<pair<int,int>> byEnd = vector<pair<int,int>>(N);
        for (int i=0 ; i<N ; i++) {
            auto it = position.find(snowSeq[i]);
            if (it == position.end()) {
                position.insert(pair<int,int>(snowSeq[i], i));

            } else {
                byStart[position.at(snowSeq[i])] = pair<int,int>(position.at(snowSeq[i]), i);
                byEnd[i] = pair<int,int>(position.at(snowSeq[i]), i);
            }
        }
        int max_length = 0;
        int length = 0;
        for (int i = 0 ; i < N ; i++) {
            pair<int,int> seg1 = byStart.at(i);
            if (seg1 == pair<int,int>(0,0)) {
                byStart[i] = pair<int,int>(i, N);
                byEnd[N-1] = pair<int,int>(i, N);
            } else {
                byEnd.at(seg1.second) = pair<int,int>(0,0);
            }
            length = seg1.second-seg1.first;

            pair<int,int> seg2 = byEnd.at(i);
            int curr = seg1.second-1;
            while (seg2 == pair<int,int>(0,0) && curr < N) {
                seg2 = byEnd.at(curr++);
            }
            if (seg2.first>=seg1.first && seg2.second<=seg1.second) {
                length = seg2.second-seg1.first;
            }
            max_length = max(max_length, length);
        }
        cout << max_length << endl;
    }
}