#ifndef LIST_H
#define LIST_H
#include <iostream>

class List
{
public:
    List();

    ~List();

    List(const List& other);

    List& operator=(List const& other); // kopieringstilldelningsoperator, kopiering till befintligt objekt

    List(List&& other);//flyttkonstruktor List l2 {std::move(l1)}, skapar list l2 och byter pekare

    List& operator=(List && other); //byt pekare mellan två objekt

    void clear();

    bool is_empty() const;

    void insert(int value);

    int size() const;

    std::string print() const;

    void remove(int);

private:
    
    struct Node
    {
        int value;
        Node* next;
    };
Node* head;

};

#endif
