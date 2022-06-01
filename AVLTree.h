#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <iostream>
#include <math.h>
#include<memory>
using namespace std;

#define DATA_EXIST 1
#define MEMORY_ERROR 2 
#define ADDED 7

//namespace MEVNY{
template<class T , class comparator>
class AVLTree;
//----------------------------------------AVL NODE IMPLEMENT------------------------------------//
template <class T,class comparator>
class AVLNode
{
    friend class AVLTree<T,comparator>;
    T data;
    AVLNode* right;
    AVLNode* left;
    AVLNode* parent;
    int height;

    public :
    AVLNode( T data);
    ~AVLNode();
    const T& getData()const;
    int getHeight()const;
    void setHeight(int height);
    AVLNode* getLeft()const;
    AVLNode* getRight()const;
    AVLNode* getParent()const;
    void setLeft( AVLNode* left);
    void setRight( AVLNode* right);
    void setParent(AVLNode* parent);

void updateHeight() {
    if(this != nullptr){
        int val = 1;

        if(this->left != nullptr){
            val = this->left->height + 1;
        }
        if(this->right != nullptr){
            if(val > this->right->height + 1){
                val = val;
            }
            else{
                val = this->right->height+1;
            }
        }
        this->height = val;
    }
}


    int balanceFactorNode(const AVLTree<T,comparator>& tree)const;
    void setData(const T data)
    {
        this->data=data;
    }
};
template<class T,class comparator>
int AVLNode<T,comparator>::balanceFactorNode(const AVLTree<T,comparator>& tree)const
{

   return tree.balanceFactor(this);
}
template<class T , class comparator>
AVLNode<T,comparator>::~AVLNode()
{
    
}
template <class T,class comparator>
const T& AVLNode<T,comparator>::getData()const
{
    return this->data;
}

template <class T,class comparator>
AVLNode<T,comparator>::AVLNode( T data):data(data),right(nullptr),left(nullptr),parent(nullptr),height(1){}


template <class T,class comparator>
AVLNode<T,comparator>*  AVLNode<T,comparator>::getLeft()const
{
    if(!this)
    {
        return nullptr;
    }
    return this->left;
}

template <class T,class comparator>
AVLNode<T,comparator>*  AVLNode<T,comparator>::getRight()const
{
    if(!this)
    {
        return nullptr;
    }
    return this->right;
}
template <class T,class comparator>
AVLNode<T,comparator>*  AVLNode<T,comparator>::getParent()const
{
    if(!this)
    {
        return nullptr;
    }
    return this->parent;
}
template <class T,class comparator>
void AVLNode<T,comparator>::setRight( AVLNode<T,comparator>* right)
{
    if(!this)return;
   this->right=right;
  if(right)right->setParent(this);
}


template<class T,class comparator>
int AVLNode<T,comparator>::getHeight()const
{
    if(this==NULL)return 0 ;
    return this->height;
}


template<class T,class comparator>
void AVLNode<T,comparator>::setHeight(int height)
{
    if(!this)return;
    this->height=height;
}


template <class T,class comparator>
void AVLNode<T,comparator>::setLeft( AVLNode<T,comparator>* left)
{
    if(!this)return;
    this->left=left;
    if(left)left->setParent(this);
}


template <class T,class comparator>
void AVLNode<T,comparator>::setParent(AVLNode<T,comparator>* parent)
{
    if(!this)return;
    this->parent=parent;
}
template<typename K, typename V>
class test_helper;

//-------------------------------------AVL TREE IMPLEMENT---------------------------------------//
template<class T,class comparator>
class AVLTree
{
    friend class test_helper<T,comparator>;
    bool check_heights(AVLNode<T,comparator>* to_update);
    AVLNode<T,comparator>* check_heights1(AVLNode<T,comparator>* to_update);
    void  updating_height(AVLNode<T,comparator>* unbalanced);
    int num_of_nodes;
    int height_of_tree;
    AVLNode<T,comparator>* maxNode;
    AVLNode<T,comparator>* minNode;
    AVLNode<T,comparator>* root;

    public:
    AVLTree();
    void DestroyRecursively(AVLNode<T,comparator>* node);
    ~AVLTree();
    int getNum_of_nodes();
    AVLNode<T,comparator>* getRoot()const ;
    AVLNode<T,comparator>* getRightSon()const;
    AVLNode<T,comparator>* getLeftSon()const;
    AVLNode<T,comparator>* getParent()const;
    AVLTree<T,comparator>* initTree();
    void setMaxNode(AVLNode<T,comparator>* max);
    AVLNode<T,comparator>* getMaxNode()const;
    void setMinNode(AVLNode<T,comparator>* minNode);
    AVLNode<T,comparator>* getMinNode()const;
    AVLNode<T,comparator>* leftLeftRotation(AVLNode<T,comparator>* unbalanced);
    AVLNode<T,comparator>* rightLeftRotation(AVLNode<T,comparator>* unbalanced);
    AVLNode<T,comparator>* rightRightRotation(AVLNode<T,comparator>* unbalanced);
    AVLNode<T,comparator>* leftRightRotation(AVLNode<T,comparator>* unbalanced);
    int AVLInsert(const T to_add);
    void AVLInsertTheNode(AVLNode<T,comparator>* to_add);
    void AVLRemoveVal(const T  to_remove);
    AVLNode<T,comparator>* AVLRemove(AVLNode<T,comparator>* iter,const T to_del);
    int balanceFactor(const AVLNode<T,comparator>* root1) const;
    AVLNode<T,comparator>* find( AVLNode<T,comparator>* root1,const T& data) ;
    AVLNode<T,comparator>* find_max_min_than( AVLNode<T,comparator>* root1,const T& data) ;
    bool isExist(AVLNode<T,comparator>* root1,const T& data);
    void  update_and_check_heights(AVLNode<T,comparator>* parent_of_the_added);
    AVLNode<T,comparator>* next_max_node();
    AVLNode<T,comparator>* next_min_node();
    AVLNode<T,comparator>* the_next_node(AVLNode<T,comparator>* node);// used in deleting 
    bool is_leaf(const AVLNode<T,comparator>* node)const;
    void update_and_check_heights_after_remove(AVLNode<T,comparator>* to_check);
    bool moveTree(AVLTree<T,comparator>& moved ,AVLTree<T,comparator>& to);
    void clear_tree(AVLTree<T,comparator>& to_clear);
    AVLNode<T,comparator>* the_next_node_iterating(AVLNode<T,comparator>* node);// used in deleting 
};
template <class T,class comparator>
void AVLTree<T,comparator>::clear_tree(AVLTree<T,comparator>& to_clear)
{
 DestroyRecursively(to_clear.root);
 to_clear.root=to_clear.minNode=to_clear.maxNode=NULL;
 to_clear.num_of_nodes=0; 
}

template <class T,class comparator>
AVLNode<T,comparator>*  AVLTree<T,comparator>::the_next_node_iterating(AVLNode<T,comparator>* node)// not checked
{
 if(node==NULL)return NULL;
AVLNode<T,comparator>* tmp =node;
//next node min than
if(node == this->minNode )//
        {
            tmp=nullptr;
        }
        else
        {
            
            if(tmp->getRight()!=nullptr)
            {
                tmp =tmp->getRight();
                while(tmp->getLeft())
                {
                    tmp=tmp->getLeft();
                }
            }
            else
            {
                AVLNode<T,comparator>* current=tmp;
                tmp=tmp->getParent();
                while(tmp->getParent() && tmp->getRight()==current)
                {
                    current=tmp;
                    tmp=tmp->getParent();
                }
            }
              
        }
return tmp ;
}


template <class T,class comparator>
bool AVLTree<T,comparator>::moveTree(AVLTree<T,comparator>& moved ,AVLTree<T,comparator>& to)
{
   AVLNode<T,comparator>* ptr= moved.getMaxNode();
  for(;ptr!=NULL; ptr=moved.the_next_node_iterating(ptr))
  {
      if(to.AVLInsert((ptr->getData()))==MEMORY_ERROR)
      {
          
          return false;
      }
  }
  return true;
}

template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::next_max_node()
{
    
if(!this ||this->num_of_nodes==0)return NULL;
    
AVLNode<T,comparator>* ptr=(this->root);
while(ptr->getLeft())
{
    ptr=ptr->getLeft();
}
 return ptr;
}
 

 
 


template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::next_min_node()
{
if(!this || this->num_of_nodes==0)return NULL;

AVLNode<T,comparator>* ptr=(this->root);
while(ptr->getRight())
{
    ptr=ptr->getRight();
}
 return ptr;
}

template <class T,class comparator>
void AVLTree<T,comparator>::AVLRemoveVal(const T to_remove)
{
    if(!isExist(this->root,to_remove))
    {
        
        return;
    }
    AVLNode<T,comparator>* to_del=find(this->root,to_remove);
    if(!to_del)return;
    AVLRemove(this->root,to_remove);
}

template <class T,class comparator>
int AVLTree<T,comparator>::getNum_of_nodes()
{
    return this->num_of_nodes;
}
template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::getRoot()const
{
    
    return this->root;
}

template <class T,class comparator>
AVLTree<T,comparator>::AVLTree():num_of_nodes(0),height_of_tree(0),maxNode(nullptr),minNode(nullptr),root(nullptr){}
template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::getRightSon()const
{
    return root->getRight();
}
template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::getLeftSon()const
{
    return root->getLeft(); 
}
template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::getParent()const
{
    
    return root->getParent();
}

template <class T,class comparator>
void AVLTree<T,comparator>::setMaxNode(AVLNode<T,comparator>* max)
{
    this->maxNode=max;
}
template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::getMaxNode()const
{
    return this->maxNode;
}
template <class T,class comparator>
void AVLTree<T,comparator>::setMinNode(AVLNode<T,comparator>* minNode)
{
    this->minNode=minNode;
}
template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::getMinNode()const
{
    return this->minNode;
}



template <class T,class comparator>
void AVLTree<T,comparator>::updating_height(AVLNode<T,comparator>* unbalanced)
{
   if(unbalanced->getRight() && unbalanced->getLeft())
   { 
       unbalanced->setHeight(max((unbalanced->getRight())->getHeight(),(unbalanced->getLeft())->getHeight())+1);
   }else if(unbalanced->getRight())
    {
        unbalanced->setHeight((unbalanced->getRight())->getHeight()+1);
    }else if(unbalanced->getLeft())
    {
        unbalanced->setHeight((unbalanced->getLeft())->getHeight()+1);
    }
    else
    {
        unbalanced->setHeight(1);
    } 
}

template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::leftLeftRotation(AVLNode<T,comparator>* unbalanced)
{
    //parent of unbalanced
    AVLNode<T,comparator>* parent = unbalanced->getParent();
    bool right = false ,  left =false;
    
    if(parent->getRight()==unbalanced)right=true;
    if(parent->getLeft()==unbalanced)left=true;
    AVLNode<T,comparator>* new_root= unbalanced->getLeft();
    AVLNode<T,comparator>* temp= (unbalanced->getLeft())->getRight();
    (unbalanced->getLeft())->setRight(unbalanced);
    unbalanced->setLeft(temp);

    //unbalanced->setParent(new_root);
    if(unbalanced==this->root)
    {
        this->root=new_root;
    }
     new_root->setParent(parent);
   if(right)
   {
     if(parent)parent->setRight(new_root);
   }

   if(left)
   {
     if(parent) parent->setLeft(new_root);
   }
   //update height - only the unbalanced that was in the beginning- maybe must update the others also !!!
    updating_height(unbalanced);

    new_root->height=max(new_root->getRight()->getHeight(),new_root->getLeft()->getHeight())+1;
    return new_root;
}

template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::rightLeftRotation(AVLNode<T,comparator>* unbalanced)
{//reminder :update parent ,root and height 
  AVLNode<T,comparator>* new_root=leftLeftRotation(unbalanced->getRight());

  unbalanced->setRight(new_root);
 
  return rightRightRotation(unbalanced);
}

template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::rightRightRotation(AVLNode<T,comparator>* unbalanced)
{
    AVLNode<T,comparator>* parent = unbalanced->getParent();
    bool right = false ,  left =false;
    if(parent->getRight()==unbalanced)right=true;
    if(parent->getLeft()==unbalanced)left=true;
      AVLNode<T,comparator>* new_root= unbalanced->getRight();
    
    AVLNode<T,comparator>* temp= (unbalanced->getRight())->getLeft();
    (unbalanced->getRight())->setLeft(unbalanced);
    unbalanced->setRight(temp);

    // unbalanced->setParent(new_root);
    if(unbalanced==this->root)
    {
        root=new_root;
    }
   new_root->setParent(parent);
   if(right)
   {
     parent->setRight(new_root);
   }

   if(left)
   {
      parent->setLeft(new_root);
   }
   
 //update height - only the unbalanced that was in the beginning- maybe must update the others also !!!
    updating_height(unbalanced);

    new_root->height=max(new_root->getRight()->getHeight(),new_root->getLeft()->getHeight())+1;



    return new_root;
}


template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::leftRightRotation(AVLNode<T,comparator>* unbalanced)
{
   
  AVLNode<T,comparator>* new_root=rightRightRotation(unbalanced->getLeft());
  unbalanced->setLeft(new_root);
 
  return leftLeftRotation(unbalanced);

  
}

template <class T,class comparator>
int AVLTree<T,comparator>::balanceFactor(const AVLNode<T,comparator>* root1) const
{
    if(root1==nullptr)
    {
        return 0;
    }
    
    if(!root1->getLeft())return 0-root1->getRight()->getHeight();
    if(!root1->getRight())return root1->getLeft()->getHeight();
    return (root1->getLeft())->getHeight() - (root1->getRight())->getHeight();
}

template <class T,class comparator>
void AVLTree<T,comparator>::AVLInsertTheNode(AVLNode<T,comparator>* to_add)
{
    if(!(this->root))
    {
        this->maxNode=to_add;
        this->minNode=to_add;
        this->root=this->minNode;
        return;
    }//size 0 
    AVLNode<T,comparator>* parent = this->root;
    comparator cmp;

    while (true)
    {
      
        if(cmp(to_add->getData(),parent->getData())<0)
                {
                    if(!parent->getRight())
                    {
                        parent->setRight(to_add);
                        break;
                    }
                    parent=parent->getRight();
                    
                }
        if(cmp(to_add->getData(),parent->getData())>0)
                {
                    if(!parent->getLeft())
                    {
                        parent->setLeft(to_add);
                        break;
                    }
                parent=parent->getLeft();
                    
                }
         
    }
    // checking heights and roll
    
    if(parent)update_and_check_heights(parent);

}

template<class T,class comparator>
 AVLNode<T,comparator>* AVLTree<T,comparator>::check_heights1( AVLNode<T,comparator>* to_update)
{

int bf=balanceFactor(to_update);
 
if(bf>=2)
{
    if(balanceFactor(to_update->getLeft())<0)
    {
     to_update= leftRightRotation(to_update);
    }
    else
    {
       to_update=leftLeftRotation(to_update);
    }
  
}
if(bf<=-2)
{
       
       if(balanceFactor(to_update->getRight())<=0)
     {
         
       to_update=rightRightRotation(to_update);
     }
     else
     {
        to_update=rightLeftRotation(to_update);
     }

}
return to_update;
}

template<class T,class comparator>
bool AVLTree<T,comparator>::check_heights( AVLNode<T,comparator>* to_update)
{

int bf=balanceFactor(to_update);
 
if(bf>=2)
{
    if(balanceFactor(to_update->getLeft())<0)
    {
      leftRightRotation(to_update);
    }
    else
    {
       leftLeftRotation(to_update);
    }
    return true;
}
if(bf<=-2)
{
       
       if(balanceFactor(to_update->getRight())<=0)
     {
         
       rightRightRotation(to_update);
     }
     else
     {
        rightLeftRotation(to_update);
     }
return true;
}
return false;
}
template<class T,class comparator>
void AVLTree<T,comparator>::update_and_check_heights(AVLNode<T,comparator>* parent_of_the_added)
{
   
    AVLNode<T,comparator>* to_check=parent_of_the_added;//->getParent();

    while(to_check!=this->getRoot())

    {  
    to_check->setHeight( max(to_check->getRight()->getHeight(),to_check->getLeft()->getHeight())+1);
    if(is_leaf(to_check))to_check->setHeight(1);
     check_heights(to_check);// bool was_rotated =
    to_check->setHeight( max(to_check->getRight()->getHeight(),to_check->getLeft()->getHeight())+1);
    if(is_leaf(to_check))to_check->setHeight(1);
 
 to_check=to_check->getParent();
    
    }
    check_heights(to_check);
}


template <class T,class comparator>
int   AVLTree<T,comparator>::AVLInsert(const T to_add)
{
    if(find(root,to_add))
    {
        return DATA_EXIST;
    }
    AVLNode<T,comparator>* new_node;
    try{
        new_node=new AVLNode<T,comparator>(to_add);
    }catch(std::bad_alloc& e){}
    //is check that allocation work needed
    AVLInsertTheNode(new_node);
    comparator cmp;
if(this->num_of_nodes==0){this->maxNode=new_node;
  this->minNode=new_node;
}


if(cmp(to_add,(this->maxNode)->getData())>0)this->maxNode=new_node;
if(cmp(to_add,(this->minNode)->getData())<0)this->minNode=new_node;

    this->num_of_nodes++;
    return ADDED;
}

template<class T,class comparator>
bool AVLTree<T,comparator>::is_leaf(const AVLNode<T,comparator>* node)const
{
    return (!(node->getLeft() ||  node->getRight()));
}

template<class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::the_next_node(AVLNode<T,comparator>* node)// used in deleting 
{
    if(!node)return nullptr;
    AVLNode<T,comparator>* tmp =node;
    //min node in subtree

    while(tmp->getLeft())
    {
        tmp=tmp->getLeft();
    }
    //next node max than
    return tmp;
}
template<class T,class comparator> 
 void AVLTree<T,comparator>::update_and_check_heights_after_remove(AVLNode<T,comparator>* to_check)
 {
   
       while(to_check)
       {
        int before=to_check->getHeight();
        if(is_leaf(to_check))
        {
            to_check->setHeight(1);
        }else
        {
            to_check->setHeight(max(to_check->getRight()->getHeight(),to_check->getLeft()->getHeight())+1);
        }
        check_heights(to_check);
        int height=to_check->getHeight();
        to_check=to_check->getParent();
       }
 }





template <class T,class comparator>
static void swapNodesData(AVLNode<T,comparator>* node1, AVLNode<T,comparator>* node2)
{
    const T temp = node1->getData();
    node1->setData(node2->getData());
    node2->setData(temp);
}

template<class T,class comparator> 
AVLNode<T,comparator>* AVLTree<T,comparator>::AVLRemove(AVLNode<T,comparator>* iter,const T to_del)
{
    if (!iter) {
        return nullptr;
    }

    comparator cmp;
    if(cmp(to_del,iter->getData())>0) {
        iter->setLeft(AVLRemove(iter->getLeft(), to_del));
        iter->updateHeight();
    } else if(cmp(to_del,iter->getData())<0) {
        
        iter->setRight(AVLRemove(iter->right,to_del));
        iter->updateHeight();
    } else {    //this is the node to remove.

        if (!iter->right && !iter->left) {
    if(iter!=this->root){if(iter==iter->getParent()->getRight())iter->getParent()->setRight(nullptr);
            if(iter==iter->getParent()->getLeft())iter->getParent()->setLeft(nullptr);
            }
            delete iter;
            this->num_of_nodes--;
            iter = nullptr;
            this->maxNode=next_max_node();
            this->minNode=next_min_node();
            if(this->num_of_nodes==0)this->root=nullptr;

              
             
          

        } else if (!iter->right) { // no right 
            swapNodesData(iter, iter->left);
            iter->setLeft(AVLRemove(iter->left, to_del));

        } else if (!iter->left) { // no left 
            swapNodesData(iter, iter->right);
            iter->setRight( AVLRemove(iter->right, to_del));

        } else {// both sides exist
            AVLNode<T,comparator>* temp = iter->right;
            while (temp->left) {    // get the next  in order
                temp = temp->left;

            }
            swapNodesData(iter, temp);
            iter->setRight(AVLRemove(iter->right, to_del));

        }
    }

    if (iter==nullptr) {
        return nullptr;
    }
 
    iter->updateHeight();
    iter=check_heights1(iter);
    iter->updateHeight();
   


    return iter;
}


template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::find( AVLNode<T,comparator>* root1,const T& data)
{ 
    if(!root1 || this->num_of_nodes==0){
        return NULL;
    }
    comparator cmp;
    const T& tmp=root1->getData();
    if(cmp(tmp,data)==0)
    {
        return root1;
    }
    if(cmp(tmp,data)<0)
    {
        return find(root1->getLeft(),data);
    }
    else
    {
        return find(root1->getRight(),data);
    }

}
template <class T,class comparator>
AVLNode<T,comparator>* AVLTree<T,comparator>::find_max_min_than( AVLNode<T,comparator>* root1,const T& data)// not checked
{
    if(!root1 || this->num_of_nodes==0){
        return NULL;
    }
    comparator cmp;
    //if(root1->getData()==data)
    const T& tmp=root1->getData();

    if(!root1->getLeft() &&cmp(tmp,data)<=0)return root1;
    if(cmp(tmp,data)==0 )
    {
        return root1;
    }

    const T& tmp_r=root1->getLeft()->getData();
    
    //if((root1)->getData()>data)
    if(cmp(tmp,data)<0 && cmp(tmp_r,data)>0 )
    {
        return root1;
    }
    else if(cmp(tmp,data)<0 )
    {
        return find_max_min_than(root1->getLeft(),data);
    }      
          return find_max_min_than(root1->getRight(),data);
      


}

template <class T,class comparator>
bool AVLTree<T,comparator>::isExist(AVLNode<T,comparator>* root1,const T& data)
{
    if(find(root,data))
    {
        return true;
    }
    return false;
}




template <class T,class comparator>
void AVLTree<T,comparator>::DestroyRecursively(AVLNode<T,comparator>* node)
{
    if (node)
    {
        DestroyRecursively(node->getLeft());
        DestroyRecursively(node->getRight());
        delete node;
    }
}

template <class T,class comparator>
AVLTree<T,comparator>::~AVLTree()
{
    DestroyRecursively(this->root);
}
#endif
