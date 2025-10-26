#include <iostream>
#include <string>
#include <vector>

int countVoid(std::string line)
{
    bool space = false;
    bool right = false;
    int amountOfVoid = 0;
    for(char c : line)
    {
        if (c == 'X')
        {
            if (space)
                right = true;
            space = false;
        }
        else
        {
            space = true;
            ++amountOfVoid;
        }
        if (right)
            return amountOfVoid;
    }
    return amountOfVoid;
}

int countSum(std::vector<int> &v, int sub)
{
    int sum = 0;
    for (int i = 0; i < v.size(); i++)
    {
        sum += v[i] - sub;
    }
    return sum;
}

int main()
{
    std::string line;
    std::vector<int> v;
    int leastAmountOfVoid = 0;
    int n = 0;
    while(getline(std::cin, line))
    {
        try
        {
            n = std::stoi(line);
            if (!v.empty())
                std::cout << countSum(v, leastAmountOfVoid) << std::endl;
            if (n == 0)
                return 0;
            leastAmountOfVoid = 0;
            v.clear();
        }
        catch (...)
        {
            int s = countVoid(line);
            if (v.empty())
            {
                leastAmountOfVoid = s;
            }
            else if (leastAmountOfVoid > s)
            {
                leastAmountOfVoid = s;
            }
            v.push_back(s);
        }
    }
    return 0;
}