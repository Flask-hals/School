#include <iomanip> //för utskrift av frequency och table
#include <string>
#include <iostream> //utskrift
#include <sstream>  //inmatning från användaren
#include <vector>
#include <map> //för frequency och table
#include <fstream>
#include <iterator>
#include <algorithm>

void OpenFile(std::string const &ThisFile, std::vector<std::string> &text)
{
    std::ifstream MyFile(ThisFile);
    if (MyFile.is_open())
    {
        copy(std::istream_iterator<std::string>{MyFile},
             std::istream_iterator<std::string>{},
             back_inserter(text));
    }
}

//----------------------------------------------------------

void print(std::vector<std::string> const &text)
{
    std::copy(text.begin(), text.end(),
              std::ostream_iterator<std::string>{std::cout, " "});
    std::cout << std::endl;
}

//----------------------------------------------------------

std::map<std::string, int> frequency(std::vector<std::string> const &text)
{
    std::map<std::string, int> mCount{};
    std::for_each(text.begin(), text.end(),
                  [&mCount](std::string const &str)
                  {
                      mCount[str]++;
                  });
    return mCount;
}

//----------------------------------------------------------

std::vector<std::pair<std::string, std::string>> split(std::string const &str, std::vector<std::pair<std::string, std::string>> &FlagParameter)
{
    if (std::find(str.begin(), str.end(), '=') != str.end())
    {
        std::istringstream ss(str);
        std::string arg1;
        std::string arg2;

        std::getline(ss, arg1, '=');
        std::getline(ss, arg2);
        FlagParameter.push_back(make_pair(arg1, arg2));
        return FlagParameter;
    }
    else
    {
        FlagParameter.push_back(make_pair(str, ""));
        return FlagParameter;
    }
}

//----------------------------------------------------------

void SortMap(std::vector<std::pair<std::string, int>> &mVector, std::string const &longest, bool change)
{
    std::sort(mVector.begin(), mVector.end(),
              [&change](std::pair<std::string, int> const &a, std::pair<std::string, int> const &b)
              {
                    if (change)
                    {
                        return a.first < b.first;
                    }
                    else
                    {
                        return a.second > b.second;
                    }
              });

    std::for_each(mVector.begin(), mVector.end(),
                  [&longest, &change](const std::pair<std::string, int> &a)
                  {
                    if (change)
                    {
                        std::cout << std::left << std::setw(longest.size()+1)
                                << a.first
                                << a.second << std::endl;
                    }
                    else
                    {
                      std::cout << std::right << std::setw(longest.size()+1)
                                << a.first
                                << a.second << std::endl;
                    }
                  });
}

//----------------------------------------------------------

auto longest(std::vector<std::pair<std::string, int>> &mVector)
{
    auto longest = std::max_element(mVector.begin(), mVector.end(),
                                    [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
                                    {
                                        return a.first.size() < b.first.size();
                                    });
    return longest->first;
}

//----------------------------------------------------------

void remove(std::vector<std::string> &text, std::string const &remover)
{
    if(text.empty())
    {
        throw std::logic_error("Wrong");
    }

    auto it = std::find(text.begin(), text.end(), remover);
    if (it == text.end())
    {
        throw std::logic_error ("Wrong");
    }

    text.erase(std::remove(text.begin(), text.end(), remover),
               text.end());
}

//----------------------------------------------------------

std::pair<std::string, std::string> substitute(std::string const &str)
{
    if (str.empty())
    {
        throw std::logic_error ("Wrong");
    }

    std::pair<std::string, std::string> sub{};
    if (std::find(str.begin(), str.end(), '+') != str.end())
    {
        std::istringstream ss(str);
        std::string arg1;
        std::string arg2;

        std::getline(ss, arg1, '+');
        std::getline(ss, arg2);
        sub = std::make_pair(arg1, arg2);
        return sub;
    }
    else
    {
        throw std::logic_error ("Wrong");
    }
}

std::vector<std::string> replace(std::vector<std::string> &text, std::string const &arg1, std::string const &arg2)
{

    if (std::find(text.begin(), text.end(), arg1) == text.end())
    {
        throw std::logic_error ("Wrong");
    }
    else
    {
        std::replace(text.begin(), text.end(), arg1, arg2);
        return text;
    }
}

//----------------------------------------------------------

void UpdateData(std::vector<std::string> const &text,
                std::map<std::string, int> &mCount,
                std::vector<std::pair<std::string, int>> &mVector)
{
    mCount = frequency(text);
    mVector.clear();
    std::copy(mCount.begin(), mCount.end(), back_inserter(mVector));
}


//----------------------------------------------------------

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 3)
        {
            throw std::logic_error ("Wrong");
        }
    }
    catch (const std::logic_error& i)
    {
        std::cerr << "To few arguments" << std::endl;
        return 1;
    }

    std::vector<std::string> text;
    std::vector<std::string> TmpArguments{argv, argv + 2};
    // Första två kommandoradsargumenten
    std::vector<std::string> arguments{argv + 2, argv + argc};
    // Resterande kommandoradsargument
    std::vector<std::pair<std::string, std::string>> FlagParameter{};
    // Pair med flag respektive parameter
    std::map<std::string, int> mCount{};
    // Map som innehåller orden i text och hur ofta de förekommer
    std::vector<std::pair<std::string, int>> mVector;
    // Används för att skriva ut --table och --frequency

    OpenFile(TmpArguments[1], text);

    std::transform(arguments.begin(), arguments.end(), arguments.begin(),
                   [&FlagParameter](std::string const &str)
                   {
                       split(str, FlagParameter);
                       return str;
                   });

    std::for_each(FlagParameter.begin(), FlagParameter.end(),
                  [&text, &FlagParameter, &mCount, &mVector, &TmpArguments](const auto &flag)
                  {
                      if (flag.first == "--print")
                      {
                          print(text);
                      }
                      if (flag.first == "--frequency")
                      {
                          UpdateData(text, mCount, mVector);
                          std::string longestString = longest(mVector);
                          SortMap(mVector, longestString, false);
                      }
                      if (flag.first == "--table")
                      {
                          UpdateData(text, mCount, mVector);
                          std::string longestString = longest(mVector);
                          SortMap(mVector, longestString, true);
                      }
                      if (flag.first == "--remove")
                      {
                          try
                          {
                              remove(text, flag.second);
                              UpdateData(text, mCount, mVector);
                          }
                          catch (const std::logic_error& i)
                          {
                              std::cerr << "Wrong format" << std::endl;
                          }
                      }
                      if (flag.first == "--substitute")
                      {
                          try
                          {
                              std::pair<std::string, std::string> sub{substitute(flag.second)};
                              replace(text, sub.first, sub.second);
                              UpdateData(text, mCount, mVector);
                          }
                          catch (const std::logic_error& i)
                          {
                              std::cerr << "Wrong format" << std::endl;
                          }
                      }
                  });

    return 0;
}