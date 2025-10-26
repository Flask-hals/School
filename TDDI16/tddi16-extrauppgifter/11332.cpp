#include <iostream>
#include <string>

int sumDigits(int sum, std::string input)
{
    for (char c : input)
    {
        int dig = c - '0';
        sum += dig;
    }
    if (sum > 9)
        sum = sumDigits(0, std::to_string(sum));
    return sum;
}

int main() {
    std::string line;
    while (std::getline(std::cin, line))
    {
        if (line != "0")
        {
            std::cout << sumDigits(0, line) << std::endl;
        }
        else
            break;
    }
    return 0;
}