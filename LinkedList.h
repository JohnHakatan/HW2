#ifndef LINKED_LIST_H
#define LINKED_LIST_H
using namespace std;
//need to add exeptions
template <class T>
class ListNode
{
    public:
    T data;
    int id;
    ListNode* next;
    ListNode(T data ,int id ): data(data),id(id),next(nullptr){}
    ~ListNode()=default;
};

template <class T>
class LinkedList
{
    public:
    ListNode<T> *head;
    LinkedList():head(nullptr),size(0){}
    ~LinkedList(){this->DestroyList();}
    // {
    //     ListNode<T>* to_delete=this->head;
    //     ListNode<T>* previous=to_delete;
    //     while (to_delete)
    //     {
    //         to_delete->next;
    //         delete previous;
    //         previous=to_delete;
    //     }
        
    // }
    void Insert(int id,T data);
    void InsertInStart(T data,int id);
    void RemoveNode(int id);
    void DestroyList();
    ListNode<T>* Find(int id);
    int size;
    int get_size()
    {
        return this->size;
    }
};

template <class T >
void LinkedList<T>::InsertInStart(T data,int id)
{
    if( !this->head)
    {
        this->head=new ListNode<T>(nullptr,0);
        head->next=new ListNode<T>(data,id);
        this->size++;
        return;
    }

    ListNode<T>* new_node= new ListNode<T>(data,id);
    new_node->next=head->next;
    head->next=new_node;
    this->size++;
}
template <class T>
void LinkedList<T>::Insert(int id,T data)
{
    if(!this->head)
    {
        this->head=new ListNode<T>(nullptr,0);
        head->next=new ListNode<T>(data,id);
        this->size++;
        return;
    }
   // ListNode<T>* new_node= new ListNode<T>(data,id);
    ListNode<T>* current=this->head;
    ListNode<T>* previous=this->head;

    do{
        current=current->next;
        if(!current)
        {
            //current=new_node;
            current=new ListNode<T>(data,id);
            previous->next=current;
            this->size++;
            return;
        }
        previous=current;
    }while(current);
    
}

template <class T>
void LinkedList<T>::RemoveNode(int id)
{
    if(id==0|| this->size==0)return;
    // if(!Find(id))
    // {
    //     return;
    // }
    ListNode<T>* current=this->head;
    ListNode<T>* previous=this->head;
    while(current)
    {
        if(current->id==id)
        {
            previous->next=current->next;
            delete current;
            this->size--;
            return;
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
    if(!this->head)return;
    ListNode<T>* current=this->head;
    ListNode<T>* previous;
    while(current)
    {
        previous=current;
        current=current->next;
        delete previous;
    }
    
   // delete this;
}

template <class T>
ListNode<T>* LinkedList<T>::Find(int id)
{
    if(!this)return nullptr;
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
    return nullptr;
}

#endif