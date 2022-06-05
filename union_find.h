#ifndef UNION_FIND_H_
#define UNIT_FIND_H_

#include <iostream>
using namespace std;

template<class T,class comparator>
class union_find{
    T** groups;
   //parent pointer must be in T with set and get
    int current_size;
    int initial_size;

    public:
    // 
    void init()
    {

        for (int i = 0; i < initial_size; i++)
        {
            groups[i]=new T(i,i);//company with id and value = i 
            
        }
        
    }
    
    
    union_find(int n)
    {
       
        groups=new (T*)[n];
        current_size=n;
         initial_size=n;
           init();
    }
   
     T* find_(T* group,int id)
    {
        if (group->parent==NULL) {//THERE ARE NO PARENT

            return group; 
        }
        T* to_rtn=find(groups[id]->getParent(),groups[id]->getId());
        groups[id]->setParent(to_rtn);
        return to_rtn;
    }
     T* find(int id)
    {
        if(groups[id]==nullptr)//no group
        return nullptr;
        if(id > initial_size)//there is no id like that
        return nullptr;
        return find_(groups[id],id);
    }

    void union(int id1,int id2)
    {
        T* t1=find(id1);
        T* t2=find(id2);
        if( id1==id2||t1->getId()==t2->getId() )
        return;

        t1->moveEmployees(t2);//moving trees and updating father and point the moved one to the bigger one  
    }


~union_find()
    {
        for(int i=0;i<current_size;i++)
        {
            delete groups[i];
        }
     delete groups;
    }
};



#endif