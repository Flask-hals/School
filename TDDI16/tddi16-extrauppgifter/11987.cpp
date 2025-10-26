#include <cstddef>
#include <iostream>
#include <vector>

using namespace std;

int find(int x, vector<int>& parent) {
    if (parent[x] == x)
        return x;
    return parent[x] = find(parent[x], parent);
}

void unions(vector<int>& size, vector<long long>& sum, vector<int>& parent, int rootP, int rootQ)
{
    if (rootP != rootQ)
    {
        parent[rootQ] = rootP;
        size[rootP] += size[rootQ];
        sum[rootP] += sum[rootQ];
        size[rootQ] = 0;
        sum[rootQ] = 0;
    }
}

void move(vector<int>& pos, vector<int>& size, vector<long long>& sum, vector<int>& parent, int first, int second)
{
    int rootP = find(pos[first], parent);
    int rootQ = find(pos[second], parent);
    if (rootP != rootQ)
    {
        size[rootP]--;
        sum[rootP] -= first;
        
        int newNode = parent.size();
        parent.push_back(newNode);
        size.push_back(1);
        sum.push_back(first);
        pos[first] = newNode;
        unions(size, sum, parent, newNode, rootQ);
    }
}

int main()
{
    int n, m;
    while(cin >> n >> m)
    {
        vector<int> pos(n+1);
        vector<long long> sum(n+1, 0);
        vector<int> size(n+1, 1);
        vector<int> parent(n+1, 0);

        for(size_t i = 1; i <= n; i++)
        {
            pos[i] = i;
            sum[i] += i;
            parent[i] = i;
        }

        for(int j = 0; j < m; j++)
        {
            int com, p, q = 0;
            cin >> com >> p;
            if (com != 3)
                cin >> q;
            if (com == 1)
                unions(size, sum, parent, find(pos[p], parent), find(pos[q], parent));
            else if (com == 2)
                move(pos, size, sum, parent, p, q);
            else
            {
                int root = find(pos[p], parent);
                cout << size[root] << " " << sum[root] << endl;
            }
        }
    }

    return 0;
}