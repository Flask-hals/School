#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

int main()
{
    unordered_set<string> s;
    string line;
    vector<string> v;
    vector<string> result;

    while (cin >> line)
    {
        s.insert(line);
        v.push_back(line);

    }

    for (string word : v)
    {
        for (int i = 1; i < word.size(); i++)
        {
            string firstPart = word.substr(0, i);
            string secondPart = word.substr(i);
            if (s.find(firstPart) != s.end() && s.find(secondPart) != s.end())
            {
                result.push_back(word);
                break;
            }
        }
    }

    for (string word : result)
        cout << word << endl;

    return 0;
}