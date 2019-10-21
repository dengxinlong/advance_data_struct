#include "rb_tree.h"

RB_tree::
RB_tree(const vector<ElemType> & nums)     //构造函数
{
    ;
}

RB_tree::
RB_tree(const RB_tree & rhs)           //拷贝构造函数
{
    ;
}


RB_tree & RB_tree::
operator=(const RB_tree & rhs)       //赋值运算符函数
{
    ;
}


pRB_node  RB_tree::
insert(const ElemType & val)
{
    pRB_node pnode = new RB_node(val);
    if (!pnode)
        return nullptr;
    // if (!_root)
    // {
    //     _root = pnode;
    //     return true;
    // }
        
    // if(search(val))
    //     return false;
    
    pRB_node ptr = _root;
    pRB_node pre = nullptr;
    while (ptr)
    {
        pre = ptr;
        if (pnode->_val < ptr->_val)
            ptr = ptr->_left;
        else
            ptr = ptr->_right;
    }

    pnode->_parent = pre;

    if (pre)
    {
        if (pnode->_val < pre->_val)
            pre->_left = pnode;
        else
            pre->_right = pnode;
    }
    else
        _root = pnode;
    //将树重新修正为一颗红黑树
    insert_fixup(pnode);
    return pnode;
}

void RB_tree::
insert_fixup(pRB_node pnode) //将树重新修正为一颗红黑树
{
    pRB_node parent, gparent;

    //若父节点存在，且父节点的颜色为红色
    while ((parent = pnode->_parent) && (parent->_color == RED))
    {
        gparent = parent->_parent;

        //若父节点是祖父结点的左孩子
        if (parent == gparent->_left)
        {
            {   //条件1：叔叔结点是红色
                pRB_node uncle = gparent->_right;
                if (uncle && uncle->_color == RED)
                {
                    uncle->_color = BLACK;
                    parent->_color = BLACK;
                    gparent->_color = RED;
                    pnode = gparent;
                    continue;
                }
            }
            
            //情况2： 叔叔结点是黑色，且当前结点是有孩子，叔叔不存在，也认为是黑色
            if (parent->_right == pnode)
            {
                pRB_node tmp;
                left_rotate(parent);            //左旋
                tmp = parent;
                parent = pnode;
                pnode = tmp;
            }

            //情况3： 叔叔是黑色，且当前结点的孩子是左孩子
            parent->_color = BLACK;
            gparent->_color = RED;
            right_rotate(gparent);
        }
        else //若父亲结点是祖父结点的右孩子
        {
            { //情况1：叔叔结点是红色
                pRB_node uncle = gparent->_left;
                if (uncle && uncle->_color == RED)
                {
                    uncle->_color = BLACK;
                    parent->_color = BLACK;
                    gparent->_color = RED;
                    pnode = gparent;
                    continue;
                }
            }

            //情况2：叔叔是黑色，且当前结点是左孩子，
            if (parent->_left == pnode)
            {
                pRB_node tmp;
                right_rotate(parent);
                tmp = parent;
                parent = pnode;
                pnode = tmp;
            }

            //情况3： 叔叔是黑色， 且当前结点是右孩子
            parent->_color = BLACK;
            gparent->_color = RED;
            left_rotate(gparent);
        }
    }

    //将根结点设置为黑色
    _root->_color = BLACK;
}

void RB_tree::
left_rotate(pRB_node pnode)
{
    pRB_node ptr = pnode->_right;

    //将 “ptr的左孩子” 设我 ”pnode的右孩子
    //如果ptr的左孩子非空，将“pnode”设为“ptr的左孩子的父亲
    pnode->_right = ptr->_left;
    if (ptr->_left)
        ptr->_left->_parent = pnode;
    
    //将pnode的父亲设为ptr的父亲
    ptr->_parent = pnode->_parent;

    if (!pnode->_parent)
    {
        _root = ptr;
    }
    else
    {
        if (pnode->_parent->_left == pnode)
            pnode->_parent->_left = ptr;
        else
            pnode->_parent->_right = ptr;
    }

    ptr->_left = pnode;
    pnode->_parent = ptr;
}

void RB_tree::
right_rotate(pRB_node pnode)
{
    pRB_node ptr = pnode->_left;
    pnode->_left = ptr->_right;
    if (ptr->_right)
        ptr->_right->_parent = pnode;
    ptr->_parent = pnode->_parent;

    if (pnode->_parent == nullptr)
    {
        _root = ptr;
    }
    else
    {
        if (pnode->_parent->_right == pnode)
            pnode->_parent->_right = ptr;
        else
            pnode->_parent->_left = ptr;
    }

    ptr->_right = pnode;
    pnode->_parent = ptr;
}   


bool RB_tree::
del(const ElemType & val)
{
    pRB_node z, pnode;
    if (z = search(val))   ///////////////////////////////////////////////////////////////////////
        return delete_node(z);
    else
        return false;
}

bool RB_tree::
delete_node(pRB_node pnode)
{
    pRB_node child, parent;
    int color;
    
    //被删除的结点的"左右孩子都不为空"的情况
    if (pnode->_left && pnode->_right)
    {
        //被删除结点的后继结点，用它来取代“被删除结点位置，然后再讲需删除结点去掉
        pRB_node replace = pnode;
        replace = replace->_right;
        while (replace->_left)
            replace = replace->_left;
        
        //pnode结点不是根结点，开始替换
        if (pnode->_parent)
        {
            if (pnode->_parent->_left == pnode)
                pnode->_parent->_left = replace;
            else
                pnode->_parent->_right = replace;
        }
        else
            _root = replace;
        
        //child是”取代结点的右孩子，也是需要调整的结点
        //“取代结点”肯定不存在左孩子，因为他是一个后继结点
        child = replace->_right;
        parent = replace->_parent;
        color = replace->_color;

        if (parent == pnode)
            parent = replace;
        else
        {
            if (child)
                child->_parent = parent;
            parent->_left = child;
            
            replace->_right = pnode->_right;
            pnode->_right->_parent = replace;
        }

        replace->_parent = pnode->_parent;
        replace->_color = pnode->_color;
        replace->_left = pnode->_left;
        pnode->_left->_parent = replace;

        //移除一个红色结点不需要调整，但是移除一个黑色结点，红黑树平衡将会打破
        if (color == BLACK)
            delete_fixup(child, parent);
        delete pnode;
        return true;
    }

    //删除结点有一边是null
    if (pnode->_left)
        child = pnode->_left;
    else
        child = pnode->_right;
    parent = pnode->_parent;
    color = pnode->_color;

    if (child)
        child->_parent = parent;
    
    //pnode结点不是根结点
    if (parent) 
    {
        if (parent->_left == pnode)
            parent->_left = child;
        else
            parent->_right = child;
    }
    else
        _root = child;
    if (color == BLACK)
        delete_fixup(child, parent);
    delete pnode;
    return true;
}

void RB_tree::
delete_fixup(pRB_node child, pRB_node parent)
{
    pRB_node other;
    while ((!child || child->_color == BLACK) && child != _root)
    {
        if (parent->_left == child)
        {
            //删除
            other = parent->_right;
            if (other->_color == RED)
            {
                other->_color = BLACK;
                parent->_color = RED;
                left_rotate(parent);
                other = parent->_right;
            }
            if ((!other->_left || other->_left->_color == BLACK) && \
                (!other->_right || other->_right->_color == BLACK))
            {
                other->_color = RED;
                child = parent;
                parent = child->_parent; 
            }
            else
            {
                if (!other->_right || other->_right->_color == BLACK)
                {
                    other->_left->_color = BLACK;
                    other->_color = RED;
                    right_rotate(other);
                    other = parent->_right;
                }
                //情况4： child的兄弟结点w是黑色，且w的右孩子是红色，左孩子任意颜色
                other->_color = parent->_color;
                parent->_color = BLACK;
                other->_right->_color = BLACK;
                left_rotate(parent);
                child = _root;
                break;
            }
        }
        else
        {
            other = parent->_left;
            if (other->_color == RED)
            {
                //情况1：child的兄弟结点是红色
                other->_color = BLACK;
                parent->_color = RED;
                right_rotate(parent);
                other = parent->_left;
            }
            if ((!other->_left || other->_left->_color == BLACK) && \
                (!other->_right || other->_right->_color == BLACK))
            {
                other->_color = RED;
                child = parent;
                parent = child->_parent;
            }
            else
            {
                if (!other->_left || other->_left->_color == BLACK)
                {
                    other->_right->_color = BLACK;
                    other->_color = RED;
                    left_rotate(other);
                    other = parent->_left;
                }

                //情况4：child的兄弟w是黑色，且w的右孩子是红色，左孩子任意颜色
                other->_color = parent->_color;
                parent->_color = BLACK;
                other->_left->_color = BLACK;
                right_rotate(parent);
                child = _root;
                break;
            }
        }
    }
    if (child)
        child->_color = BLACK;
}


pRB_node RB_tree::
search(const ElemType & val)
{
    //return find(_root, val);  //递归实现查找操作
    pRB_node ptr = _root;
    while (ptr)
    {
        if (ptr->_val == val)
            return ptr;
        
        if (ptr->_val > val)
            ptr = ptr->_left;
        else
            ptr = ptr->_right;
    }
    return nullptr;
}

bool RB_tree::
find(const pRB_node pnode, const ElemType & elem)
{
    if (!pnode)
        return false;
    else if (pnode->_val == elem)
        return true;
    
    if (elem < pnode->_val)
        return find(pnode->_left, elem);
    else 
        return find(pnode->_right, elem);
}


bool RB_tree::
clear(void)
{
    if (!_root)
    {
        destroy(_root);
        _root = nullptr;
    }
     
    return true;
}

void RB_tree::
destroy(pRB_node pnode)
{
    if (!pnode)
        return;
    if (pnode->_left)
        destroy(pnode->_left);
    if (pnode->_right)
        destroy(pnode->_right);
    delete pnode;
}


void RB_tree::
preorder() const
{
    pre_order(_root);
    cout << endl;
}

void RB_tree::
inorder() const
{
    in_order(_root); 
    cout << endl;  
}

void RB_tree::
postorder() const
{
    post_order(_root);
    cout << endl;
}

void RB_tree::
pre_order(pRB_node pnode) const
{
    if (pnode)
    {
        cout << pnode->_val << " ";
        pre_order(pnode->_left);
        pre_order(pnode->_right);
    }
}

void RB_tree::
in_order(pRB_node pnode) const
{
    if (pnode)
    {
        in_order(pnode->_left);
        cout << pnode->_val << " ";
        in_order(pnode->_right);
    }
}

void RB_tree::
post_order(pRB_node pnode) const
{
    if (pnode)
    {
        post_order(pnode->_left);
        post_order(pnode->_right);
        cout << pnode->_val << " ";
    }
}

pRB_node 
minimum(pRB_node pnode)  //查找当前树中最小的结点
{
    if (!pnode)
        return nullptr;
    while (pnode->_left)
    {
        pnode = pnode->_left;
    }
    return pnode;
}

pRB_node 
maximum(pRB_node pnode) //查找当前树中最大的结点
{
    if (!pnode)
        return nullptr;
    
    while (pnode->_right)
    {
        pnode = pnode->_right;
    }
    return pnode;
}