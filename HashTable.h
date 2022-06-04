#ifndef HASHTABLE_H
#define HASHTABLE_H


#define LOAD_FACTOR 10

#include "LinkedList.h"

template <class T>
class HashTable
{
    int size_of_array;
    int num_of_nodes;

    LinkedList<T> **dynamic_array;
    public:
    HashTable(int size);
    void Insert(T data,int key);
    //need to complete
    void Remove(int key);
    //need to complete
    ListNode<T> Find(int id);
    int hashFunction(int m);
    //need to complete
    void arrayDestroy();
};

template <class T>
int HashTable<T>::hashFunction(int key)
{
    return (key%size);
}
template <class T>
HashTable<T>::HashTable(int size)
{
    this->size=size;
    dynamic_array=new LinkedList<T>*[size]();
}


template <class T>
void HashTable<T>::Insert(T data,int key)
{
    //check if need to expend array
    if((this->num_of_nodes) /(this->size) >=LOAD_FACTOR)
    {
        //expending array by 2 and copy all the nodes to new array 
        int old_size=this->size;
        this->size=size*2;
        LinkedList<T>** new_array=new LinkedList<T>*[this->size]();
        for(int i=0 ; i<old_size ; ++)
        {
            if(this->dynamic_array[i])
            {
                ListNode<T> current=dynamic_array[i];
                while(current)
                {
                    new_array[current->id % this->size]->Insert(current->data,current->id);
                    current=current->next;
                }
            }
            this->arrayDestroy();
            this->dynamic_array=new_array;
        }
    }
    //check if there's a list in the wanted cell in the array 
    if(!dynamic_array[key%size])
    {
        dynamic_array[key%size]=new LinkedList<T>();
    }
    //inserting a new node without expending array
    (dynamic_array[key%size])->Insert(data,key);
    num_of_nodes++;
}



#endif