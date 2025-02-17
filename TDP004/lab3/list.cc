#include "list.h"
#include <string>
#include <utility>

List::List(): head {nullptr}
{}

//------------------------------------------

List::~List()
{
    while (head)
    {
    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node* tmp {head};
        while (tmp->next->next)
        {
            tmp = tmp->next;
        }
        delete tmp->next;
        tmp->next = nullptr;
    }
    }
}

//------------------------------------------

List& List::operator=(List const& other) // kopieringstilldelningsoperator, kopiering till befintligt objekt
{
    if ( this == &other )
    {
        return *this;
    }
    else
    {
        this->clear();
        List temp = List(other); // Temp används för att kopieringskonstruktorn endast tar in ett obefintligt objekt
        std::swap(temp.head, (*this).head);
        return *this;
    }
}

//------------------------------------------

List::List(List&& other)//flyttkonstruktor List l2 {std::move(l1)}, skapar list l2 och byter pekare
: head{other.head}
{
    other.head = nullptr;
} 

//------------------------------------------

List& List::operator=(List && other) //byt pekare mellan två objekt, tilldelningsoperator
{
    if (this == &other)
    {
        return *this;
    }
    else
    {
        std::swap(head, other.head);
        return *this;
    }
}

//------------------------------------------

List::List(const List& other) //Kopieringskonstruktor
    : head(nullptr)
{
    if (other.head)
    {
        head = new Node{other.head->value, nullptr};
        Node* other_tmp {other.head->next};
        Node* tmp {head};
        while (other_tmp)
        {
            tmp->next = new Node{other_tmp->value, nullptr};
            tmp = tmp->next;
            other_tmp = other_tmp->next;
        }
    }
}

//------------------------------------------

bool List::is_empty() const
{
    return head == nullptr;
}

//------------------------------------------

int List::size() const
{
    int tmp_counter {};
    Node* tmp {head};
    while (tmp != nullptr)
    {
        tmp = tmp->next;
        ++tmp_counter;
    }
    return tmp_counter;
}

//------------------------------------------

void List::insert(int value)
{
    Node* tmp {this->head};
    if (head == nullptr) //Första noden
    {
        head = new Node{value, nullptr};
    }
    else if (head->value > value) //Ifall noden ska läggas mellan objektpekaren och första noden
    {
        head = new Node{value, head};
    }
    else if (tmp->next == nullptr) // Ifall noden läggs till i slutet
    {
        tmp->next = new Node{value, nullptr};
    }
    else if ((*tmp->next).value > value) //Kollar om noden framför är större
    {
        tmp->next = new Node{value, tmp->next};
    }
    else if ((*tmp).value == value) // Ifall värdet för noden är samma
    {
        tmp->next = new Node{value, tmp->next};
    }
    else
    {
      head = head->next; // Flytta head för att tmp ska flyttas
      (*this).insert(value);
      head = tmp; // För att återställa head till början av listan
    }

}

//------------------------------------------

void List::clear()
{
    Node*& first {(*this).head};
    while (first)
    {
      if (first->next == nullptr) //Sista noden
      {
        delete first;
        first = nullptr;
      }
      else
      {
        Node* tmp {first};
        while (tmp->next->next) //Kollar två noder framför tmp
        {
          tmp = tmp->next;
        }
        delete tmp->next; //Tar bort en nod framför
        tmp->next = nullptr; //Sätter sista noden till null
      }
    }
}

//------------------------------------------

std::string List::print() const
{
    std::string result;
    Node* tmp {(*this).head};
    while ( tmp != nullptr )
    {
        result += std::to_string(tmp->value) + " ";
        tmp = tmp->next;
    }
    return result;
}

//------------------------------------------

void List::remove(int value)
{
    Node* tmp {head};
    Node* behind_tmp{head};
    while (tmp)
    {
      if (tmp->value == value)
      {
        if (head->value == value)
        {
            head = (*tmp).next;
        }
        if (tmp->next == nullptr)
        {
            behind_tmp->next = nullptr;
        }
        (*behind_tmp).next = tmp->next;
        delete tmp;
        tmp = nullptr;
      }
      else
      {
        behind_tmp = tmp;
        tmp = tmp->next;
      }
    }
}