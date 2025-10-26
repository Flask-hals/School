#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main()
{
    int n, m;
    while(cin >> n >> m)
    {
        unordered_map<int, vector<int>> um;
        int index {1};
        while(index <= n)
        {
            int element;
            cin >> element;
            um[element].push_back(index);
            index++;
        }

        while(m--)
        {
            int k, v;
            cin >> k >> v;
            if(um.find(v) != um.end())
            {
                if(um[v].size() >= k)
                {
                    cout << um[v][k-1] << endl;
                }
                else
                    cout << 0 << endl;
            }
            else
                cout << 0 << endl;
        }
    }

    return 0;
}