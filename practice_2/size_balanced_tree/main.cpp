#include "input_conf.h"
#include "rb_tree.h"

#include <stdlib.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define MAXN 100010

inline void display_data(const vector<int> data)
{
    for (const auto elem : data)
        cout << elem << " ";
    cout << endl;
}

int solution(const vector<int> & data, RB_tree & rb_tree);

int sons[MAXN][2];
int size[MAXN], data[MAXN];
int sbt = 0, sbttail = 0;

void rotate(int & t,int w) //rotate(&node,0/1)
{
	int k = sons[t][1-w];
	if (!k) return ;
	sons[t][1-w] = sons[k][w];
	sons[k][w] = t;
	size[k] = size[t];
	size[t] = size[sons[t][0]] + size[sons[t][1]]+1;
	t = k;
}

void maintain(int& t,bool flag) //maintain(&node,flag)
{
	if (!t) return ;
	if (!flag)
		if (size[sons[sons[t][0]][0]]>size[sons[t][1]]) rotate(t,1);
		else if (size[sons[sons[t][0]][1]]>size[sons[t][1]]) 
		{
			rotate(sons[t][0],0);
			rotate(t,1);
		} else return ;
	else
		if (size[sons[sons[t][1]][1]]>size[sons[t][0]]) rotate(t,0);
		else if (size[sons[sons[t][1]][0]]>size[sons[t][0]])
		{
			rotate(sons[t][1],1);
			rotate(t,0);
		} else return ;
	
	maintain(sons[t][0],false);
	maintain(sons[t][1],true);
	maintain(t,false);
	maintain(t,true);
}

void insert(int & t, int v,int pos) //insert(&root,value,pos/0)
{
	if (!size[t])
	{
		if (!pos)
		{
			sbttail++;
			pos=sbttail;
		}
		data[pos]=v;
		size[pos]=1;
		sons[pos][0]=0;
		sons[pos][1]=0;
		t=pos;
	} else 
	{
		size[t]++;
		if (v<data[t]) insert(sons[t][0],v,pos);
		else insert(sons[t][1],v,pos);
		maintain(t,v>=data[t]);
	}
}

int last; //last node
int del(int& t,int v) //value=del(&root,key)
{
	size[t]--;
	if (v==data[t]||(v<data[t]&&sons[t][0]==0)||(v>data[t]&&sons[t][1]==0))
	{
		int ret=data[t];
		if (sons[t][0]==0||sons[t][1]==0) 
		{
			last=t;
			t=sons[t][1]+sons[t][0];
		}
		else data[t]=del(sons[t][0],data[t]+1);
		return ret;
	} else
	if (v<data[t]) return del(sons[t][0],v);
	else return del(sons[t][1],v);
}

int delk(int& t,int k) //value=del(&root,k)
{
	size[t]--;
	if (size[sons[t][0]]+1==k)
	{
		int ret=data[t];
		if (sons[t][0]==0||sons[t][1]==0) 
		{
			last=t;
			t=sons[t][1]+sons[t][0];
		}
		else data[t]=delk(sons[t][0],data[t]+1);
		return ret;
	} else
	if (k<=size[sons[t][0]]) return delk(sons[t][0],k);
	else return delk(sons[t][1],k-1-size[sons[t][0]]);
}

int select(int t,int k) //node=select(root,k)
{
	if (k==size[sons[t][0]]+1) return t;
	if (k<=size[sons[t][0]]) return select(sons[t][0],k);
	else return select(sons[t][1],k-1-size[sons[t][0]]);
}

int search(int t,int x) //node=search(root,x)
{
	if (t==0||x==data[t]) return t;
	if (x<data[t]) return search(sons[t][0],x);
	else return search(sons[t][1],x);
}

void deb_out()
{
	printf("-------\n");
	printf("sbttail=%d sbt=%d\n",sbttail,sbt);
	for	(int i=1;i<=sbttail;i++)
	printf("%2d: key=%2d size=%2d left=%2d right=%2d\n",i,data[i],size[i],sons[i][0],sons[i][1]);
	printf("-------\n");
}

int main(int argc, char ** argv)
{
    if (argc != 2) 
    {
        cout << "argument is error.\n";
        exit(-1);
    }

    vector<int> data = input_data(argv[1]);             //将数据文进中的内容读取到vector中

    sbttail = 0;
	sbt = 0;

    int min = solution(data, sbt);
    cout << "min: " << min << endl;



    return 0;
}

int solution(const vector<int> & data, RB_tree & rb_tree)
{
    int sum = data[0];

    insert(sbt, data[0],0);
    for (int i = 1; i < data.size(); ++i)
    {
        //cout << "i = " << i << endl;
        insert(sbt, data[i], 0);
        
    }

    return sum;
}