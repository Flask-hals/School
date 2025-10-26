#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

struct Node 
{
    int marbles;
    vector<int> children;
};

int compute(unordered_map<int, Node>& um, int& cost, int node)
{
    int surplus = um[node].marbles - 1;
    for (int i = 0; i < um[node].children.size(); i++)
    {
        int childSurplus = compute(um, cost, um[node].children[i]);
        surplus += childSurplus;
        cost += abs(childSurplus);
    }
    return surplus;
}

int findRoot(vector<int>const& v, unordered_map<int, Node> const& um)
{

    for(const auto& keyValue : um)
    {
        bool root = true;
        for (int i = 0; i < v.size(); i++)
        {
            if (keyValue.first == v[i])
            {
                root = false;
                break;
            }
        }
        if (root)
            return keyValue.first;
    }
    return 0;
}

int main()
{
    string line;
    unordered_map<int, Node> um;
    int counter = 0;
    int nodes = 0;
    vector<int> v;


    while(getline(cin, line))
    {
        int n = 0;
        int marbles = 0;
        int children = 0;
        int child = 0;

        if (line == "0")
            return 0;
        else if (counter == 0)
        {
            nodes = stoi(line);
            counter++;
        }
        else
        {
            stringstream ss (line);
            ss >> n >> marbles >> children;
            um[n] = Node{marbles, {}};

            while (ss >> child)
            {
                v.push_back(child);
                um[n].children.push_back(child);
            }
            counter++;
            if (counter-1 == nodes)
            {
                int cost = 0;
                compute(um, cost, findRoot(v, um));
                cout << cost << endl;
                nodes = 0;
                counter = 0;
                um.clear();
                v.clear();
            }
        }
    }
    return 0;
}