#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node
{
    bool visited;
    vector<int> v;
};

vector<int> BFS(int startNode, vector<Node>& nodes)
{
    vector<int> notVisited;
    queue<int> q;
    q.push(startNode);

    while (!q.empty())
    {
        int curr = q.front(); q.pop();
        for (int x : nodes[curr].v) {
            if (!nodes[x].visited) {
                nodes[x].visited = true;
                q.push(x);
            }
        }
    }

    for (int i = 1; i <= nodes.size() - 1; i++)
    {
        if (!nodes[i].visited)
            notVisited.push_back(i);
    }

    vector<int> retNotVisited;
    retNotVisited.push_back(notVisited.size());

    for (int t : notVisited)
        retNotVisited.push_back(t);
    return retNotVisited;
}

int main()
{
    int n;
    while (cin >> n && n != 0)
    {
        vector<Node> nodes(n +1);
        int i;
        while(cin >> i && i != 0)
        {
            int j;
            while(cin >> j && j != 0)
            {
                nodes[i].v.push_back(j);
            }
        }
        int k;
        cin >> k;
        vector<int> startNodes(k);
        for(int id = 0; id < k; id++)
            cin >> startNodes[id];

        for (auto x : startNodes)
        {
            for(int i = 1; i <= n; i++)
                nodes[i].visited = false;
            vector<int> notVisited = BFS(x, nodes);
            cout << notVisited[0];
            for (int nv = 1; nv < notVisited.size(); nv++)
                cout << " " << notVisited[nv];
            cout << endl;
        }
            
    }
    
    return 0;
}