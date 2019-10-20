#include "input_conf.h"

vector<int> input_data(string input_file)
{
    vector<int> data;
    ifstream input(input_file);
    
    int value;
    while (input >> value)
    {   
        data.push_back(value);
    }
    return data;
}