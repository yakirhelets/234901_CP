#include <iostream>
#include <unordered_set>
#include <vector>
#include <set>

using namespace std;

int main ()
{
    int TC;
    cin >> TC;
    while (TC--)
    {
        bool res = true;
        int lakes_num = 0;
        int forecast_days = 0;
        cin >> lakes_num;
        vector<int> lakes = vector<int>(lakes_num);
        for (int i=0 ; i<lakes_num ; i++) {
            lakes[i] = 1;
        }

        cin >> forecast_days;
        int zeros = 0;

        vector<int> days = vector<int>(forecast_days);
        for (int i=0 ; i<forecast_days ; i++) {
            cin >> days[i];
            if(days[i] == 0) {
                zeros++;
            }
        }

        vector<int> dragon = vector<int>(zeros);

        if (days[0] != 0 || zeros < days.size() - zeros) {
            res = false;
        } else {
            int curr = 0;
            for (int i=0 ; i<forecast_days ; i++) {
                if (days[i] != 0) {
                    if (curr <= zeros) {
                        dragon[curr] = days[i];
                        curr++;
                    } else {
                        res = false;
                    }
                }
            }
        }
        int curr = 0;
        for (int i=0 ; i<forecast_days ; i++) {
            if (days[i] == 0) {
                if (dragon[curr] != 0 && --lakes[dragon[curr]-1] < 0) {
                    res = false;
                    break;
                }
                curr++;
            } else {
                if (++lakes[days[i] - 1] > 1) {
                    res = false;
                    break;
                }
            }
        }

        if (!res) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            for (int i=0 ; i<dragon.size() ; i++) {
                cout << dragon[i] << " ";
            }
            cout << endl;
        }
    }
}