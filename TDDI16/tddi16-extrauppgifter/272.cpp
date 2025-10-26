#include <iostream>
#include <string>

void converter()
{
    std::string line;
    std::string input;
    bool first = true;
    while (std::getline(std::cin, line))
    {
        input += line;
        input += "\n";
    }
    for (char c : input)
    {
        if (c == '"')
        {
            if (first)
            {
                std::cout << "``";
                first = false;
            }
            else
            {
                std::cout << "''";
                first = true;
            }
            }
            else
                std::cout << c;
        }
}

int main() {
    converter();
    return 0;
}