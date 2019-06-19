#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
    public:

    bool isEnd;
    int rank;
    vector<Node> next;

    Node()
    {
        isEnd = false;
        rank = 0;
        next.reserve(10);
    }
};

int main()
{
    int t, n, i;
    string pnum;
    Node* v = NULL;

    cin >> t;
    while (t--)
    {
        Node trie;
        bool consistent = true;

        cin >> n;
        while (n--)
        {
            cin >> pnum;
            v = &trie;

            for (i = 0; i < pnum.size() && consistent; i++)
            {
                if (v->rank == 0) v->next.resize(10);
                v->rank++;
                if (v->isEnd) consistent = false;
                v = &v->next[pnum[i] - '0'];
            }
            v->isEnd |= (i == pnum.size());
            if (v->rank > 0 && v->isEnd) consistent = false;

        }
        cout << ((consistent) ? "YES\n" : "NO\n");
    }
    return 0;
}