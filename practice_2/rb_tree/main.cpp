#include "input_conf.h"
#include "rb_tree.h"

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

inline void display_data(const vector<int> data)
{
    for (const auto elem : data)
        cout << elem << " ";
    cout << endl;
}

int solution(const vector<int> & data, RB_tree & rb_tree);

int main(int argc, char * *argv)
{
    if (argc != 2) 
    {
        cout << "argument is error.\n";
        exit(-1);
    }

    vector<int> data = input_data(argv[1]);             //将数据文进中的内容读取到vector中
   // display_data(data);
    RB_tree rb_tree;
    int min = solution(data, rb_tree);
    cout << "min: " << min << endl;
    
    // rb_tree.inorder();
    // cout << rb_tree.del(65) << endl;
    // rb_tree.inorder();

    return 0;
}

int solution(const vector<int> & data, RB_tree & rb_tree)
{
    int sum = data[0];

    rb_tree.insert(data[0]);
    for (int i = 1; i < data.size(); ++i)
    {
        //cout << "i = " << i << endl;
        pRB_node ptr = rb_tree.insert(data[i]);
        if (ptr->_parent)
            sum += abs(ptr->_parent->_val - ptr->_val);
        else
        {
            pRB_node pmin_node = minimum(ptr->_right);
            pRB_node pmax_node = maximum(ptr->_left);
            sum += abs(ptr->_val - pmin_node->_val) < \
                   abs(ptr->_val - pmax_node->_val) ? \
                   abs(ptr->_val - pmin_node->_val) : \
                   abs(ptr->_val - pmax_node->_val);
        }
    }

    return sum;
}