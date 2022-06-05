#ifndef LINKED_LIST_H
#define LINKED_LIST_H

using namespace std;

template <class T>
class ListNode
{
    public:
    T data;
    int id;
    ListNode *next;
    ListNode(T data ,int id ): (data(data),id(id),next(nullptr)){}
    ~ListNode()=default;
};

template <class T>
class LinkedList
{
    public:
    ListNode<T> *head;
    LinkedList():head(nullptr){}
    ~LinkedList()=default;
    void Insert(T data,int id);
    void RemoveNode(int id);
    void DestroyList();
    ListNode<T>* Find(int id);
};

template <class T>
void LinkedList<T>::Insert(T data,int id)
{
    if(!this->head)
    {
        this->head=new ListNode<T>();
        head->next=new ListNode<T>(data,id);
        return;
    }
    ListNode<T>* new_node= new ListNode<T>(data,id);
    ListNode<T>* current=this->head;
    do{
        current=current->next;
        if(!current)
        {
            current=new_node;
            return;
        }
    }while(current)
}

template <class T>
void LinkedList<T>::RemoveNode(int id)
{
    if(!find(id))
    {
        return;
    }
    ListNode<T>* current=this->head->next;
    ListNode<T>* previous=this->head;
    while(current)
    {
        if(current->id==id)
        {
            previous->next=current->next;
            delete current;
        }
        else{
            previous=current;
            current=current->next;
        }
    }
}

template <class T>
void LinkedList<T>::DestroyList()
{
    ListNode<T> current=this->head;
    ListNode<T> previous=this->head;
    while(current)
    {
        current=current->next;
        delete previous;
    }
}

template <class T>
ListNode<T>* LinkedList<T>::Find(int id)
{
    ListNode<T>* current=this->head;
    while(current)
    {
        current=current->next;
        if(!current)
        {
            return nullptr;
        }
        if(current->id==id)
        {
            return current;
        }
    }
}

#endif 