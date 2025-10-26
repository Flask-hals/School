#include <iostream>
#include <string>
#include <sstream>

void encryption()
{
    std::string line;
    std::string output;
    while (std::getline(std::cin, line))
    {
        std::string s, t;
        std::stringstream ss(line);
        ss >> s >> t;
        bool found = true;
        std::size_t pos = 0;
        for (char c : s)
        {
            pos = t.find(c, pos);
            if (pos == std::string::npos)
            {
                found = false;
                break;
            }
            ++pos;
        }
        if (found)
            output += "Yes\n";
        else
            output += "No\n";
    }
    std::cout << output;
}

int main() {
    encryption();
    return 0;
}