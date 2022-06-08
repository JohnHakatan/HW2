#ifndef UNION_FIND_H_
#define UNIT_FIND_H_

#include <iostream>
using namespace std;

template<class T>
class UnionFind{
   // int *rank;
     T** parent; 
     T** pointers;
     int n;
 
public:
    // Constructor to create and
    // initialize sets of n items
    UnionFind(int n)
    {
       // rank = new int[n];
        parent = new T*[n];
        pointers = new T*[n];
        this->n = n;
        makeSet();
    }
 
    // Creates n single item sets
    void makeSet()
    {
        for (int i = 0; i < n; i++) {
            parent[i] =new T(i,i);
            pointers[i]=parent[i];
        }
    }
 
    // Finds set of given item x
    T* findd(int x)
    {
        // Finds the representative of the set
        // that x is an element of
        if (parent[x]->getId() != x) {
 
            // if x is not the parent of itself
            // Then x is not the representative of
            // his set,
            parent[x] = findd(parent[x]->getId());
 
            // so we recursively call Find on its parent
            // and move i's node directly under the
            // representative of this set
        }
 
        return parent[x];
    }
    int find(int x)
    {
        return findd(x)->getId();
    }
 
    // Do union of two sets represented
    // by x and y.
    void printFamily(int x)
    {
int id=find(x);
for(int i=0;i<n;i++)
{
    if(find(parent[i]->getId())==id)
    cout<<i<<endl;
}
//cout<<parent[458]->getId()<<endl;
    }


    bool unioun_groups_no_checking(int addTo,int toAdd)
    {
     if(addTo==toAdd)return false;
     int xset = findd(addTo)->getId();
     int yset = findd(toAdd)->getId();
        
             // If they are already in same set
        if (xset == yset)
            return false;

        T* to_move=parent[yset];
        parent[yset] = findd(xset);
        parent[yset]->moveEmployees(to_move);
    


    }
    void union_groups(int x, int y)
    {
   
if(x==y)return;
        // Find current sets of x and y
        int xset = findd(x)->getId();
        int yset = findd(y)->getId();
        
             // If they are already in same set
        if (xset == yset)
            return;
 
        // Put smaller ranked item under
        // bigger ranked item if ranks are
        // different
        T* to_move=nullptr;
        if (parent[xset]->size < parent[yset]->size) {
            to_move=parent[xset];
            parent[xset] = findd(yset);
            parent[xset]->moveEmployees(to_move);
         // rank[yset] = rank[yset] + 1;
        
        }
        else if (parent[xset]->size > parent[yset]->size) {
              to_move=parent[yset];
            parent[yset] = findd(xset);
             parent[yset]->moveEmployees(to_move);
     //   rank[xset] = rank[xset] + 1;
        }
 
        // If ranks are same, then increment
        // rank.
        else {
            
            if(yset < xset){
                   to_move=parent[yset];
            parent[yset] = findd(xset);
             parent[yset]->moveEmployees(to_move);
      //  rank[xset] = rank[xset] + 1;
        /*
            parent[yset] = findd(xset);
              rank[xset] = rank[xset] + 1;*/
              
            }
            else
            {
           /* parent[xset] = findd(yset);
              rank[yset] = rank[yset] + 1;*/
               to_move=parent[xset];
            parent[xset] = findd(yset);
            parent[xset]->moveEmployees(to_move);
         // rank[yset] = rank[yset] + 1;
            }
          
        }
    }
    ~UnionFind()
    {
        for(int i=0;i<this->n;i++)
        {
            delete pointers[i];
        }
        delete[] pointers;
        delete[] parent;
    }
};
/*
template<class T>
class UnionFind{
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
            
            groups[i] = new T(i,i);//company with id and value = i 
            
        }
        
    }
    
    
    UnionFind(int n)
    {
       
        groups = new T*[n];
        current_size=n;
         initial_size=n;
           init();
    }
   
     T* find_(T* group,int id)
    {
       // if(!group)return nullptr;
        if (group->getParent()==NULL) {//THERE ARE NO PARENT
            if(group->getId()!=id)groups[id]->setParent(group);
            return group; 
        }

        T* to_rtn=find_(group->getParent(),id);
       // group->setParent(to_rtn);
    
        return to_rtn;

    }
     T* findd(int id)
    {
        if(id > initial_size)//there is no id like that
        return nullptr;

        if(groups[id]==nullptr)//no group
        return nullptr;
        
        return find_(groups[id],id);
    }
    int find(int id)
    {
        return findd(id)->getId();
    }
    
    void union_groups(int id1,int id2)
    {
        T* t1=findd(id1);
        T* t2=findd(id2);
        if( id1==id2||t1->getId()==t2->getId() )
        return;
       if(t1->size == t2->size){ if(id2 <id1)
        {
               t1->getParent()?t2->setParent(t1->getParent()):t2->setParent(t1);
              t1->moveEmployees(t2);
           
  
        }else{
           t2->getParent()?t1->setParent(t2->getParent()):t1->setParent(t2);
    t2->moveEmployees(t1);
        }
        
       }
       else if(t1->size > t2->size)
       { t1->getParent()?t2->setParent(t1->getParent()):t2->setParent(t1);
           t1->moveEmployees(t2);//move data of t2 to t1 
                                 //moving trees and updating father and point the moved one to the bigger one

       
       }else
       {
            
t2->getParent()?t1->setParent(t2->getParent()):t1->setParent(t2);
           t2->moveEmployees(t1);
          
       }

       if(id2 < id1)
        {
               t1->getParent() ? t2->setParent(t1->getParent()):t2->setParent(t1);
          
               t1->moveEmployees(t2);
  
        }else{
           t2->getParent() ? t1->setParent(t2->getParent()):t1->setParent(t2);
            t2->moveEmployees(t1);
       
        }

    

    }


~UnionFind()
    {
        for(int i=0;i<current_size;i++)
        {
            delete groups[i];
        }
     delete groups;
    }
};*/



#endif