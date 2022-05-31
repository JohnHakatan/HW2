#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
#include <math.h>
#include <memory>
using namespace std;


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

        if(this->right != nullptr){
            val = this->right->height + 1;
        }
        if(this->left != nullptr){
            if(val < this->left->height + 1){
                val = this->left->height+1;
            }  
        }
        this->height = val;
    }
}


    int balanceFactorNode(const AVLTree<T,comparator>& tree)const;
    void setData( T data)
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
//template <class T,class comparator>
//AVLNode<T,comparator>::AVLNode() :data(),right(nullptr),left(nullptr),parent(nullptr),height(0){}

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


//-------------------------------------AVL TREE IMPLEMENT---------------------------------------//
template<class T,class comparator>
class AVLTree
{
    
}

#endif
