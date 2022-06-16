#ifndef UNION_FIND_H_
#define UNIT_FIND_H_

#include <iostream>
using namespace std;

template<class T>
class UnionFind{
   // int *rank;
     
 
public:
  T** parent; 
     T** pointers;
     int n;
    UnionFind(int n)
    {
       // rank = new int[n];
        parent = new T*[n];
        pointers = new T*[n];
        this->n = n;
        makeSet();
    }

    void makeSet()
    {
        for (int i = 0; i < n; i++) {
            parent[i] =new T(i,i);
            pointers[i]=parent[i];
        }
    }
 

    T* findd(int x)
    {
        // Finds the representative of the set
        // that x is an element of
        
        if(x >= this->n)return nullptr;// check this
        if (parent[x]->getId() != x) {
 
           
            parent[x] = findd(parent[x]->getId());

 
        }
         
 
        return parent[x];
    }
    
    int find(int x)
    {

        return findd(x)->getId();
    }
 
    void printFamily(int x)
    {
int id=find(x);
for(int i=0;i<n;i++)
{
    if(find(parent[i]->getId())==id)
    cout<<i<<endl;
}

    }


    bool unioun_groups_no_checking(int addTo,int toAdd)
    {
     if(addTo==toAdd)return false;
     int xset = findd(addTo)->getId();
     int yset = findd(toAdd)->getId();
        
             // If they are already in same set
        if (xset == yset)
            return false;

       // T* to_move=parent[yset];
        parent[yset] = findd(xset);
        
        //parent[yset]->moveEmployees(to_move);
    return true;


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



#endif