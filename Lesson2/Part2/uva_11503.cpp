#include <iostream>
#include <unordered_set>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <map>


using namespace std;

struct unionfind
{
    vector<int> rank;
    vector<int> sizes;
    vector<int> parent;
    unionfind(int size)
    {
        sizes=vector<int>(size);
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
        {
            parent[i]=i;
            sizes[i]=1;
        }
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }
    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p)
        {
            //already in the same group
            cout << sizes[p] << endl;
            return;
        }
        if(rank[p] < rank[q]) {
            parent[p] = q;
            sizes[p] += sizes[q];
            sizes[q] = sizes[p];
            cout << sizes[p] << endl;
        }
        else {
            parent[q] = p;
            sizes[q] += sizes[p];
            sizes[p] = sizes[q];
            if (rank[p] == rank[q]) rank[p]++;
            cout << sizes[q] << endl;
        }
    }
};

int main ()
{
    int TC;
    int F = 0;
    cin >> TC;
    while (TC--)
    {
        cin >> F;
        unionfind groups = unionfind(2*F);
        map<string, int> hash;
        string f1;
        string f2;
        int count = 0;
        while (F--) {
            cin >> f1;
            cin >> f2;
            if (!hash.insert(pair<string, int>(f1, count++)).second) {
                count--;
            }
            if (!hash.insert(pair<string, int>(f2, count++)).second) {
                count--;
            }
            groups.Union(hash.at(f1), hash.at(f2));
        }
    }
    return 0;
}