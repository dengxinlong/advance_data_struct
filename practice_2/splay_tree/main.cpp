#include "splay_tree.h"
#include "input_conf.h"

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int solution(const vector<int> & data, Splay_tree<int> & s_tree);

int main(int argc, char ** argv)
{
    if (argc != 2) 
    {
        cout << "argument is error.\n";
        exit(-1);
    }

    vector<int> data = input_data(argv[1]);             //将数据文进中的内容读取到vector中
    //display_data(data);
    Splay_tree<int> splay_tree;

    int min = solution(data, splay_tree);
    cout << "min: " << min << endl;

    return 0;
}

int solution(const vector<int> & data, Splay_tree<int> & splay_tree)
{
    int sum = data[0];

    splay_tree.insert(data[0]);
    for (int i = 1; i < data.size(); ++i)
    {
        splay_tree.insert(data[i]);
        int left_max = splay_tree.left_maximum();
        int right_min = splay_tree.right_minimum();
        sum += abs(left_max - data[i]) < abs(right_min - data[i]) \
               ? abs(left_max - data[i]) : abs(right_min - data[i]);
    }

    return sum;
}