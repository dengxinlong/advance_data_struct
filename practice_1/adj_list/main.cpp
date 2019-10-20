/*
 *说明：本代码使用邻接表来实现图的着色问题
 */
#include "adj_list.h"

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <map>

//#define DEBUG

using std::vector;
using std::cout;
using std::endl;
using std::set;
using std::map;

void create_adj_graph(vector<Vertex_node> & graph_vec, std::istream & input = std::cin);
void display_adj_graph(const vector<Vertex_node> & graph_vec);
int colour_adj_graph(vector<Vertex_node> & graph_vec, map<int, set<Vertex_type>> & colors);

int main(void)
{
    vector<Vertex_node> graph_vec;
    std::ifstream input_file("./config");
    create_adj_graph(graph_vec, input_file);

    //cout << "总共有";
    map<int, set<Vertex_type>> colors;
    int count = colour_adj_graph(graph_vec, colors);
    cout << "共有: " << count << endl;

    for (const auto & elem : colors)
    {
        cout << "Color" << elem.first << ": ";
        for (const auto & ver : elem.second)
        {
            cout << ver << " ";
        }
        cout << endl;
    }

#ifdef DEBUG
    display_adj_graph(graph_vec);
#endif

    exit(0);
}

void create_adj_graph(vector<Vertex_node> & graph_vec, std::istream & input)
{
    int vertex_n, arc_n;            //图的顶点个数和边数
    cout << "please enter graph's number of vertex and arc：";
    input >> vertex_n >> arc_n;

    graph_vec.resize(vertex_n);
    for (int i = 0; i < vertex_n; ++i)                      //初始化邻接表
    {
        graph_vec[i]._data = i + 1;
        graph_vec[i]._first_arc = nullptr;
        graph_vec[i]._color = None;
    }
    
    cout << "please enter side: " << endl;
    int vertex1, vertex2;
    for (int i = 0; i < arc_n; ++i)
    {
        input >> vertex1 >> vertex2;         //中间以空格隔开
        Arc_node * ptr = new Arc_node;
        ptr->_data = vertex2;
        ptr->_next = graph_vec[vertex1 - 1]._first_arc;
        graph_vec[vertex1 - 1]._first_arc = ptr;

        ptr = new Arc_node;
        ptr->_data = vertex1;
        ptr->_next = graph_vec[vertex2 - 1]._first_arc;
        graph_vec[vertex2 - 1]._first_arc = ptr;
    }
}

int colour_adj_graph(vector<Vertex_node> & graph_vec, map<int, set<Vertex_type>> & colors)
{
     //进行图的着色
    int color = None;
    for (auto & vertex : graph_vec)
    {
        if (vertex._color)
            continue;

        color++;
        vertex._color = color; 
        colors[color].insert(vertex._data);
        Arc_node * arc_ptr = vertex._first_arc;
        //查找与该顶点相连的所有顶点
        set<Vertex_type> linked_vertex;     //set的底层实现是红黑树，查找一个元素的时间复杂度是O(logN)，所以这里使用set
        while (arc_ptr)
        {
            linked_vertex.insert(arc_ptr->_data);
            arc_ptr = arc_ptr->_next;
        }

        set<Vertex_type> unlinked_vertex;
        for (int i = 0; i < graph_vec.size(); ++i)              //因为图中顶点的数据就是从1开始，所以这里可以利用
        {
            auto iter = linked_vertex.find(i + 1);
            if (iter == linked_vertex.end())
                unlinked_vertex.insert(i + 1);
        }

        if (unlinked_vertex.size())
        {
            for (auto elem : unlinked_vertex)
            {
                if (!graph_vec[elem - 1]._color)
                {
                    graph_vec[elem - 1]._color = color;
                    colors[color].insert(elem);
                }
            }  
        }
    }

    return color;
}


void display_adj_graph(const vector<Vertex_node> & graph_vec)
{
    for (const auto & elem : graph_vec)
    {
        auto ptr = elem._first_arc;
        cout << "顶点为：" << elem._data << " "
             << "color: " << elem._color << " "
             << "边为：";
        while (ptr != nullptr)
        {
            cout << ptr->_data << " ";
            ptr = ptr->_next;
        }
        cout << endl;
    }
}