#ifndef __SPLAY_TREE_H__
#define __SPLAY_TREE_H__

#include <functional>
#include <iostream>

using namespace std;

template<typename T, typename Comp = std::less<T>>
class Splay_tree 
{
public:
    Splay_tree( ) 
    : root( 0 )
    , p_size( 0 ) 
    {}

    struct node 
    {
        node *left, *right;
        node *parent;
        T key;
        node( const T& init = T( ) ) 
        : left( nullptr )
        , right( nullptr )
        , parent( nullptr )
        , key( init ) 
        {}

    } *root;
    
    void insert( const T &key ) 
    {
        node *z = root;
        node *p = 0;
        
        while( z ) 
        {
            p = z;
            if( comp( z->key, key ) ) 
                z = z->right;
            else 
                z = z->left;
        }
        
        z = new node( key );
        z->parent = p;
        
        if( !p ) 
            root = z;
        else if( comp( p->key, z->key ) ) 
            p->right = z;
        else 
            p->left = z;
        
        splay( z );
        p_size++;
    }
    
    node* find( const T &key ) 
    {
        node *z = root;
        while( z ) 
        {
            if( comp( z->key, key ) ) 
                z = z->right;
            else if( comp( key, z->key ) ) 
                z = z->left;
            else 
                return z;
        }
        return 0;
    }
            
    void erase( const T &key ) 
    {
        node *z = find( key );
        if( !z ) return;
        
        splay( z );
        
        if( !z->left ) 
            replace( z, z->right );
        else if( !z->right ) 
            replace( z, z->left );
        else 
        {
            node *y = subtree_minimum( z->right );
            if( y->parent != z ) 
            {
                replace( y, y->right );
                y->right = z->right;
                y->right->parent = y;
            }
            replace( z, y );
            y->left = z->left;
            y->left->parent = y;
        }
        
        p_size--;
    }
    
    T right_minimum() 
    { 
        node * ptr;
        if (ptr = subtree_minimum( root->right ))
            return ptr->key; 
        else
            return 0;
    }
    T left_maximum() 
    { 
        node * ptr;
        if (ptr = subtree_maximum( root->left ))
            return ptr->key; 
        else
            return 0;
    }
    
    bool empty( ) const { return root == 0; }
    unsigned long size( ) const { return p_size; }

    //中序遍历该二叉树
    void inorder(void)
    {
        if (root)
        {
            inorder(root);
        }
    }

    void inorder(node * ptr)
    {
        if (ptr)
        {
            inorder(ptr->left);
            cout << ptr->key << " ";
            inorder(ptr->right);
        }
    }

private:
    Comp comp;
    unsigned long p_size;
    
    void left_rotate( node *x ) 
    {
        node *y = x->right;
        x->right = y->left;
        if( y->left )
            y->left->parent = x;

        y->parent = x->parent;

        if( !x->parent ) 
            root = y;
        else if( x == x->parent->left ) 
            x->parent->left = y;
        else 
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }
    
    void right_rotate( node *x ) 
    {
        node *y = x->left;
        x->left = y->right;
        if( y->right ) 
            y->right->parent = x;
        y->parent = x->parent;

        if( !x->parent ) 
            root = y;
        else if( x == x->parent->left ) 
            x->parent->left = y;
        else 
            x->parent->right = y;

        y->right = x;
        x->parent = y;
    }
    
    void splay( node *x ) 
    {
        while( x->parent ) 
        {
            if( !x->parent->parent ) 
            {
                if( x->parent->left == x ) right_rotate( x->parent );
                else left_rotate( x->parent );
            } 
            else if( x->parent->left == x && x->parent->parent->left == x->parent ) 
            {
                right_rotate( x->parent->parent );
                right_rotate( x->parent );
            } 
            else if( x->parent->right == x && x->parent->parent->right == x->parent ) 
            {
                left_rotate( x->parent->parent );
                left_rotate( x->parent );
            } 
            else if( x->parent->left == x && x->parent->parent->right == x->parent ) 
            {
                right_rotate( x->parent );
                left_rotate( x->parent );
            } 
            else 
            {
                left_rotate( x->parent );
                right_rotate( x->parent );
            }
        }
    }
    
    void replace( node *u, node *v ) 
    {
        if( !u->parent ) 
            root = v;
        else if( u == u->parent->left ) 
            u->parent->left = v;
        else 
            u->parent->right = v;
        if( v ) 
            v->parent = u->parent;
    }
    
    node* subtree_minimum( node *u ) 
    {
        if (!u) 
            return nullptr;
        while( u->left ) u = u->left;
        return u;
    }
    
    node* subtree_maximum( node * u ) 
    {
        if (!u)
            return nullptr;
        while( u->right ) u = u->right;
        return u;
    }

};










#endif 