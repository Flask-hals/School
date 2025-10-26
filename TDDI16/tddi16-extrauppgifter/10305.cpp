#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> kahn(vector<int>& v)
{
    vector<int> result;
    queue<int> q;
    for (int i = 1; i < v.size(); i++) {
        if (v[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty())
    {
        int node = q.front(); q.pop();
        result.push_back(node);
        for (int i = 1; i < v.size(); i++)
        {
            v[i]--;
            if (v[i] == 0)
                q.push(i);
        }
    }
    return result;
}

int main()
{
    int n, m;
    while(cin >> n >> m && (n != 0 || m != 0))
    {
        vector<int> v(n+1, 0);
        for (int k = 0; k < m; k++)
        {
            int i, j;
            cin >> i >> j;
            v[j]++;
        }
        vector<int> res = kahn(v);
        cout << res[0];
        for(int r = 1; r < res.size(); r++)
            cout << " " << res[r];
        cout << endl;
    }

    return 0;
}