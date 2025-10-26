#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

void calcSalary(unordered_map<string, int> um, string description)
{
    stringstream ss (description);
    string word;
    int totalSalary = 0;
    while (ss >> word)
    {
       if (um.find(word) != um.end())
       {
            totalSalary += um[word];
       }
    }
    cout << totalSalary << endl;
}

int main()
{
    string line;
    string job;
    string description;
    int salary;
    bool first = true;
    int jobs;
    int descriptions;
    unordered_map<string, int> um;
    int dotCount = 0;

    while (getline(cin, line))
    {
        stringstream ss(line);
        if (first)
        {
            first = false;
            ss >> jobs >> descriptions;
        }
        else if (um.size() < jobs)
        {
            ss >> job >> salary;
            um.insert({job, salary});
        }
        else
        {
            if (line != ".")
            {
                description += line + "\n";
            }
            else
            {
                calcSalary(um, description);
                dotCount++;
                description = "";
                if (dotCount == descriptions)
                {
                    first = true;
                    jobs = 0;
                    descriptions = 0;
                    description = "";
                    dotCount = 0;
                    um.clear();
                }
            }
        }

    }
    return 0;
}