#ifndef HASHTABLE_H
#define HASHTABLE_H

#define INIT_FACTOR 10
#define LOAD_FACTOR 1
//need to add exeptions

#include "LinkedList.h"

template <class T>
class HashTable
{
    int size_of_array;
    int num_of_nodes;

    LinkedList<T> **dynamic_array;
    public:
    HashTable();
    ~HashTable(){arrayDestroy();}
    void Insert(T data,int key);
    void Remove(int key);
    ListNode<T> Find(int id);
    int hashFunction(int m);
    void arrayDestroy();
    int get_size(){
        return size_of_array;
    }
    LinkedList<T> get_element(int i)
    {
        return this->dynamic_array[hashFunction(i)];
    }
};

template <class T>
int HashTable<T>::hashFunction(int key)
{
    this->num_of_nodes=0;
    return (key%this->size_of_array);
}
template <class T>
HashTable<T>::HashTable()
{
    this->size_of_array=INIT_FACTOR;
    this->dynamic_array=new LinkedList<T>*[INIT_FACTOR]();
}


template <class T>
void HashTable<T>::Insert(T data,int key)
{
    double expending_factor=(this->num_of_nodes) /(this->size_of_array);
    //check if need to expend array
    if( expending_factor>=LOAD_FACTOR)
    {
        //expending array by 2 and copy all the nodes to new array 
        int old_size=this->size_of_array;
        this->size_of_array=this->size_of_array*2;
        LinkedList<T>** new_array=new LinkedList<T>*[this->size_of_array]();
        for(int i=0 ; i<old_size ; i++)
        {
            if(this->dynamic_array[i])
            {
                ListNode<T> current=(this->dynamic_array[i])->head->next;
                while(current)
                {
                    new_array[current->id % this->size_of_array]->Insert(current->data,current->id);
                    current=current->next;
                }
            }
            this->arrayDestroy();
            this->dynamic_array=new_array;
        }
    }
    //check if there's a list in the wanted cell in the array 
    if(!this->dynamic_array[key%this->size_of_array])
    {
        this->dynamic_array[key%this->size_of_array]=new LinkedList<T>();
    }
    //inserting a new node without expending array
    (this->dynamic_array[key%size_of_array])->Insert(data,key);
    this->num_of_nodes++;
}
template <class T>
void HashTable<T>::Remove(int key)
{
    if(!find(key))return;
    LinkedList<T> to_delete_from=this->dynamic_array[key%size_of_array];
    to_delete_from->RemoveNode(key);
    this->num_of_nodes--;
    double shrink_factor=num_of_nodes/size_of_array;
    if(shrink_factor<0.5)
    {
        //shrinking the array by 2 and copy all the nodes to new array 
        int old_size=this->size_of_array;
        this->size_of_array=size_of_array/2;
        LinkedList<T>** new_array=new LinkedList<T>*[this->size_of_array]();
        for(int i=0 ; i<old_size ; i++)
        {
            if(this->dynamic_array[i])
            {
                ListNode<T> current=(this->dynamic_array[i])->head->next;
                while(current)
                {
                    new_array[current->id % size_of_array]->Insert(current->data,current->id);
                    current=current->next;
                }
            }
            this->arrayDestroy();
            this->dynamic_array=new_array;
        }
    }

}
template <class T>
ListNode<T> HashTable<T>::Find(int id)
{
    return this->dynamic_array[hashFunction(id)]->Find(id);
}

template <class T>
void HashTable<T>::arrayDestroy()
{
    for(int i=0; i<this->size_of_array;i++)
    {
        this->dynamic_array[i]->DestroyList();
    }
    delete[] this->dynamic_array;
}


#endif
