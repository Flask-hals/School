#include "list.h"

int main()
{
    List l{};
    l.insert(5);
    l.insert(3);
    l.insert(9);
    l.insert(7);

    List l2 = l;


    l2.remove(5);

    std::cout << l.print() << std::endl;
    std::cout << l2.print() << std::endl;

    l.print();

    return 0;

}