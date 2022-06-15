#ifndef HASHTABLE_H
#define HASHTABLE_H

#define INIT_FACTOR 10
#define LOAD_FACTOR 1
//need to add exeptions
#include "library2.h"
#include "LinkedList.h"

template <class T>
class HashTable
{
    public:
    int size_of_array;
    int num_of_nodes;
    LinkedList<T> **dynamic_array;
    HashTable();
    HashTable(int size,int num_of_nodes);
    ~HashTable(){arrayDestroy();};
    StatusType insert(int key,T data);
    StatusType remove(int key);
    ListNode<T>* find(int id);
    int findd(int id);
    void OldArrayDestroy(int old_size);
    int hashFunction(int m);
    void arrayDestroy();
    void merge(HashTable<T>* ptr);
    LinkedList<T> get_element(int i)
    {
        return this->dynamic_array[hashFunction(i)];
    }
    int get_size(){
        return size_of_array;
    }
};
template<class T>
void HashTable<T>::merge(HashTable<T>* ptr)
{

    for(int i=0;i<ptr->size_of_array;i++)
    {
        if(!ptr->dynamic_array[i])continue;
        ListNode<T>* to_move=(ptr->dynamic_array[i]->head->next);
        
        while(to_move)
        {
          
            this->insert(to_move->id,to_move->data);
    
            to_move=to_move->next;
        }
    }
   // ptr->arrayDestroy();
}
template <class T>
int HashTable<T>::hashFunction(int key)
{
    return (key%this->size_of_array);
}
template <class T>
HashTable<T>::HashTable():size_of_array(INIT_FACTOR),num_of_nodes(0)
{
    this->dynamic_array=new LinkedList<T>*[INIT_FACTOR]();
    for(int i=0;i<INIT_FACTOR;i++)
    {
        this->dynamic_array[i]=nullptr;
    }
}
template <class T>
HashTable<T>::HashTable(int size,int num_of_nodes):size_of_array(size),num_of_nodes(num_of_nodes)
{
    this->dynamic_array=new LinkedList<T>*[size]();
     for(int i=0;i<size;i++)
    {
        this->dynamic_array[i]=nullptr;
    }

}


template <class T>
StatusType HashTable<T>::insert(int key,T data)
{
  
    if(find(key))return FAILURE;
    
    double expending_factor=(this->num_of_nodes) /(this->size_of_array);
    LinkedList<T>** new_array;
    //check if need to expend array
    if( expending_factor>=LOAD_FACTOR)
    {
        //expending array by 2 and copy all the nodes to new array 
        int old_size=this->size_of_array;
        this->size_of_array=this->size_of_array*2;
        
    try{
       new_array=new LinkedList<T>*[this->size_of_array]();
        //need to change the return value to allocation error
    }catch(std::bad_alloc& e){return FAILURE;}
    for(int j=0;j<this->size_of_array;j++)
    {
       new_array[j]=nullptr;
    }

        for(int i=0 ; i<old_size ; i++)
        {
            if(this->dynamic_array[i])
            {
                ListNode<T>* current=(this->dynamic_array[i])->head->next;
                while(current)
                {
                    if(!new_array[current->id % this->size_of_array])
                    {
                        new_array[current->id % this->size_of_array]=new LinkedList<T>();
                    }
                    new_array[current->id % this->size_of_array]->Insert(current->id,current->data);
                    current=current->next;
                }
            }
        }
            
        this->OldArrayDestroy(old_size);
            this->dynamic_array=new_array;
    }
    //check if there's a list in the wanted cell in the array 
    if(!this->dynamic_array[key%this->size_of_array])
    {
        dynamic_array[key%this->size_of_array]=new LinkedList<T>();
    }
    //inserting a new node without expending array
    (this->dynamic_array[key%size_of_array])->Insert(key,data);
    this->num_of_nodes++;       
    return SUCCESS;

}
template <class T>
StatusType HashTable<T>::remove(int key)
{
    if(!find(key))
    {
        return FAILURE;
    }
    LinkedList<T>* to_delete_from=this->dynamic_array[key%size_of_array];
    to_delete_from->RemoveNode(key);
    double shrink_factor=num_of_nodes/size_of_array;
    LinkedList<T>** new_array;
   
    if(shrink_factor<0.5)
    {
        
        //shrinking the array by 2 and copy all the nodes to new array 
        int new_size=this->size_of_array/2;
        try{
             new_array=new LinkedList<T>*[new_size]();
            //need to change the return value to allocation error
            }   catch(std::bad_alloc& e){return FAILURE;}
    
       for(int j=0;j<new_size;j++)
      {
            new_array[j]=nullptr;
      }
        for(int i=0 ; i<size_of_array ; i++)
        {
            if(this->dynamic_array[i]&&this->dynamic_array[i]->size>0)
            {
                ListNode<T>* current=(this->dynamic_array[i])->head->next;
                while(current)
                {
                    if(!new_array[current->id % new_size])
                    {
                        new_array[current->id % new_size]=new LinkedList<T>();
                    }
                    new_array[current->id % new_size]->Insert(current->id,current->data);
                    current=current->next;
                }
            }

        }
        arrayDestroy();
        this->dynamic_array=new_array;
        this->size_of_array=new_size;
    }
    this->num_of_nodes--;
    return SUCCESS;
}
template <class T>
ListNode<T>* HashTable<T>::find(int id)
{
    if(!(this->dynamic_array[hashFunction(id)]))return nullptr;
    return this->dynamic_array[hashFunction(id)]->Find(id);
}


template <class T>
 int HashTable<T>::findd(int id)
{
    ListNode<T>* ptr=findd(id);
    if(ptr)
    return ptr->id;

    return -1;
}

template <class T>
void HashTable<T>::OldArrayDestroy(int old_size)
{
    //ListNode<T>* current,*previous;
    for(int i=0; i<old_size;i++)
    {
       /* if(dynamic_array[i]!=nullptr)
        {
            current=dynamic_array[i]->head;
            previous=current;
            while(current)
            {
                current=current->next;
                delete previous;
                previous=current;

            }
            delete dynamic_array[i];
        }*/
        delete dynamic_array[i];
        dynamic_array[i]=nullptr;
    }

    delete[] dynamic_array;
}


template <class T>
void HashTable<T>::arrayDestroy()
{
    //ListNode<T>* current,*previous;
    for(int i=0; i<this->size_of_array;i++)
    {
       /* if(dynamic_array[i]!=nullptr)
        {
            current=dynamic_array[i]->head;
            previous=current;
            while(current)
            {
                current=current->next;
                delete previous;
                previous=current;

            }
            delete dynamic_array[i];
        }*/
        delete dynamic_array[i];
        dynamic_array[i]=nullptr;
    }

    delete[] dynamic_array;
}


#endif
