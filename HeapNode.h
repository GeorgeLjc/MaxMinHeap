#ifndef HEAPNODE_H_INCLUDED
#define HEAPNODE_H_INCLUDED
#include <stdio.h>
#include <algorithm>
#include "MaxMinHeap.h"
using namespace std;
template <class T>
class HeapNode{
    public :
        HeapNode(const T& e,const int& Number,HeapNode<T> *father){
                Num=Number;Data=e;
                fa=father;
                LeftChild=RightChild=0;
                }
        HeapNode(const T& e,const int& Number){Num=Number;Data=e;LeftChild=RightChild=fa=0;}
        HeapNode(){Data=0;Num=0;LeftChild=RightChild=fa=0;}
        ~HeapNode(){
            LeftChild=0;RightChild=0;fa=0;
        }
        void print(){cout<<Data;}
    public :
        HeapNode<T> *LeftChild,*RightChild,*fa;
        T Data;///值域
        int Num;///编号，通过编号可以得到节点所在的层是大根层还是小根层
};

#endif // HEAPNODE_H_INCLUDED
