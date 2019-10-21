#ifndef __SIZE_BALANCED_H__
#define __SIZE_BALANCED_H__

#include <iostream>
#include <vector>
#include <string>

using namespace std;



void rotate(int & t,int w);
void maintain(int& t,bool flag); //maintain(&node,flag)
void insert(int& t,int v,int pos); //insert(&root,value,pos/0)
int del(int& t,int v); //value=del(&root,key)
int delk(int& t,int k); //value=del(&root,k)
int select(int t,int k); //node=select(root,k)
int search(int t,int x); //node=search(root,x)
void deb_out();


#endif