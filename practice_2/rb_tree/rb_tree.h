#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <vector>
#include <iostream>

using namespace std;

using ElemType = int;

#define RED 0           //红色结点
#define BLACK 1            //黑色结点

typedef struct RB_node
{
    RB_node(ElemType val)
    : _val(val)
    , _color(RED)
    , _left(nullptr)
    , _right(nullptr)
    , _parent(nullptr)
    {}

    ElemType _val;
    int _color;
    RB_node * _left;
    RB_node * _right;
    RB_node * _parent;

}* pRB_node;

//定义红黑树类
class RB_tree
{
public:
    RB_tree(pRB_node root = nullptr)
    : _root(root)
    {}

    RB_tree(const vector<ElemType> & nums);     //构造函数

    RB_tree(const RB_tree & rhs);           //拷贝构造函数

    RB_tree & operator=(const RB_tree & rhs);       //赋值运算符函数

    pRB_node  insert(const ElemType & val);
    bool del(const ElemType & val);
    pRB_node search(const ElemType & val);
    bool clear(void);

    void preorder() const;
    void inorder() const;
    void postorder() const;

    pRB_node get_root(void) const
    {
        return _root;
    }

private:
    bool find(const pRB_node pnode, const ElemType & elem);

    

    void insert_fixup(pRB_node pnode); //将树重新修正为一颗红黑树

    void left_rotate(pRB_node pnode);

    void right_rotate(pRB_node pnode);

    bool delete_node(pRB_node pnode);
    void delete_fixup(pRB_node child, pRB_node parent);

    void destroy(pRB_node pnode);

    void pre_order(pRB_node pnode) const;
    void in_order(pRB_node pnode) const;
    void post_order(pRB_node pnode) const;
     
private:
    pRB_node _root;
};

pRB_node minimum(pRB_node pnode);  //查找当前树中最小的结点

pRB_node maximum(pRB_node pnode); //查找当前树中最大的结点




#endif