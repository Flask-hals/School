#include <iostream>
#include <vector>

using namespace std;

void dfs(int index, vector<int>& v, vector<int>& curr, int n, int currSum, int& bestSum, vector<int>& bestList)
{
    if (currSum > n)
        return;
    
    if (index == v.size())
    {
        if (currSum > bestSum && currSum <= n)
        {
            bestSum = currSum;
            bestList = curr;
        }
        return;
    }

    if (currSum == n)
    {
        bestSum = currSum;
        bestList = curr;
        return;
    }

    dfs(index+1, v, curr, n, currSum, bestSum, bestList);
    if (currSum + v[index] <= n) {
        curr.push_back(v[index]);
        dfs(index+1, v, curr, n, currSum + v[index], bestSum, bestList);
        curr.pop_back();
    }
}

int main()
{
    int n = 0, tracks = 0;
    while(cin >> n >> tracks)
    {
        vector<int> v;
        while (tracks--)
        {
            int track;
            cin >> track;
            v.push_back(track);
        }
        vector<int> result;
        vector<int> tmp;
        int sum = 0;
        dfs(0, v, tmp, n, 0, sum, result);
        for(int i : result)
            cout << i << " ";
        cout << "sum:" << sum << endl;
    }

    return 0;
}