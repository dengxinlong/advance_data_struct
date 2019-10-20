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

int main(int argc, char * *argv)
{
    if (argc != 2) 
    {
        cout << "argument is error.\n";
        exit(-1);
    }

    vector<int> data = input_data(argv[1]);             //将数据文进中的内容读取到vector中
    //display_data(data);
    RB_tree rb_tree;
    for (auto elem : data)
        rb_tree.insert(elem);
    
    rb_tree.inorder();

    return 0;
}