#ifndef __ADJ_LIST_H__
#define __ADJ_LIST_H__

using Vertex_type = int;

enum
{
    None = 0,
    RED,
    GREEN,
    BLACK,
    WHITE,
    BULE,
    YELLOW,
    ORIGIN,
};

struct Arc_node        //边表结点
{
    Vertex_type _data;          //存储该边
    struct Arc_node * _next;
};

struct Vertex_node          //顶点表结点
{
    Vertex_type _data;          //存储图的顶点数据
    struct Arc_node * _first_arc;
    int _color;
};




#endif