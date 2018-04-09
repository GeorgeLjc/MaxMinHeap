#ifndef MAXMINHEAP_H_INCLUDED
#define MAXMINHEAP_H_INCLUDED
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <map>
#include "HeapNode.h"
using namespace std;
template <class T>
class MaxMinHeap{
    public :
        MaxMinHeap(){Last=Top=0;Number=0;};
        ~MaxMinHeap(){delete Top;Top=0;delete Last;Last=0;};
        MaxMinHeap<T>& Insert(const T& e);
        MaxMinHeap<T>& Extract_Max(T& x);
		MaxMinHeap<T>& Extract_Min(T& x);
		MaxMinHeap<T>& Min(T& x);
		MaxMinHeap<T>& Max(T& x);
        MaxMinHeap<T>& GetLast(HeapNode<T>*& lt);
        queue<T> Search(T& e);
        queue<T> ShowElement();
        void print();
        int Size(){return Number;}
        bool IsEmpty(){return Number==0;}
        void swap(HeapNode<T>* x,HeapNode<T>* y){///交换两个节点的值
            T tmp=x->Data;x->Data=y->Data;y->Data=tmp;
            };
        void levelorder(HeapNode<T>* rt);
        void visit(HeapNode<T>* rt){cout<<rt->Data<<' '<<rt->Num<<endl;};
    private :
        HeapNode<T> *Top,*Last;///Last节点是插入位置的父节点，Top节点是根节点
        int Number;///堆中节点数目
};

template<class T>
MaxMinHeap<T>& MaxMinHeap<T>::Min(T& x) {
	if (Top == 0) return *this;
	else x = Top->Data;
	return *this;
}

template<class T>
MaxMinHeap<T>& MaxMinHeap<T>::Max(T& x) {
	if (Top == 0)return *this;
	else {
		T target = Top->Data;
		if (Top->LeftChild&&Top->LeftChild->Data > target) target = Top->LeftChild->Data;
		if (Top->RightChild&&Top->RightChild->Data > target)target = Top->RightChild->Data;
        x=target;
	}
	return *this;
}

template<class T>
MaxMinHeap<T>& MaxMinHeap<T>::Insert(const T& e){
    ///创建插入的新节点
    HeapNode<T> *NewNode=new HeapNode<T>(e,++Number,Last);
    ///判断堆是否为空
    if(Last==0){Last=Top=NewNode;}
    ///判断Last的左孩子是够已经存在
    else if(Last->LeftChild==0){
        ///如果Last左孩子为空
        Last->LeftChild=NewNode;
        ///cout<<"a "<<NewNode->Data<<' '<<NewNode->fa->Data<<endl;
    }
    else {
        ///如果Last已经存在左孩子
        ///cout<<"b "<<NewNode->Data<<' '<<NewNode->fa->Data<<endl;
        Last->RightChild=NewNode;
        HeapNode<T>* la=Last;
        HeapNode<T>* fla;///la的父节点
        ///向上搜索，查看是否存在la==fla->LeftChild这样的节点
        while(la){
            fla=la->fa;
            if(fla==0) break;///如果fla==0，说明la==Top
            if(la==fla->LeftChild) break;///找到la==fla->LeftChild这样的节点
            la=fla;
        }
        HeapNode<T>* pre=la;
        ///cout<<"c "<<pre->Data<<endl;
        ///如果la==Top,说明要开新的一排，沿着Top的左孩子一直查找到底部
        if(la==Top)
            while(la) {pre=la;la=la->LeftChild;}
        ///如果la！=Top，便沿着fla的右孩子的左孩子一直查找到底部
        else {
            la=fla->RightChild;
            while(la) {pre=la;la=la->LeftChild;}
        }
        ///pre就是要找的Last的位置
        Last=pre;
    }
    ///cout<<"Last "<<Last->Data<<endl;

    HeapNode<T>* fn;
    HeapNode<T>* cur=NewNode;
    bool f=1,l=1;
    while(l||f){///要同时满足每个层的两个条件，只要不满足就要不断向上搜索
        int k=cur->Num;
        while(k>1) k/=4;///‘1’为小根层，‘0’为大根层
        if(k==1){///k==1，在这一层的节点比父节点小，比祖父节点大
            f=l=1;
            if(cur->fa){
                fn=cur->fa;
                ///若不满足比父节点小，则要向上交换，continue重新判断
                if(cur->Data>fn->Data) {swap(cur,fn);cur=fn;continue;}
                else f=0;
                fn=fn->fa;
                if(fn){
                ///若不满足比祖父节点大，则要向上交换，continue重新判断
                    if(cur->Data<fn->Data){swap(cur,fn);cur=fn;continue;}
                    else l=0;
                }else l=0;

            }else f=l=0;
        }else{///k==0，在这一层的节点比父节点大，比祖父节点小
            f=l=1;
            if(cur->fa){
                fn=cur->fa;
                ///若不满足比父节点大，则要向上交换，continue重新判断
                if(cur->Data<fn->Data) {swap(cur,fn);cur=fn;continue;}
                else f=0;
                fn=fn->fa;
                if(fn){
                ///若不满足比祖父节点小，则要向上交换，continue重新判断
                    if(cur->Data>fn->Data) {swap(cur,fn);cur=fn;continue;}
                    else l=0;
                }else l=0;
            }else f=l=0;
        }
    }
    return *this;
}

///获得堆中最后一个节点,类似insert不过在这里是要找是否有节点是其父节点的右孩子
template<class T>
MaxMinHeap<T>& MaxMinHeap<T>::GetLast(HeapNode<T>*& lt){
    if(Last->LeftChild) {lt=Last->LeftChild;Last->LeftChild=0;}
   //else if(Last->RightChild) {lt=Last->RightChild;Last->RightChild=0;}
    else{
        HeapNode<T>* la=Last;
        HeapNode<T>* fla;
        while(la){
            fla=la->fa;
            if(fla==0) break;
            if(la==fla->RightChild) break;
            la=fla;
        }
        ///cout<<fla->Data<<endl;
        HeapNode<T>* pre=fla;
        HeapNode<T>* fp;
        if(la==Top){
            while(la) {pre=la;la=la->RightChild;}
            lt=pre;
            fp=pre->fa;
            fp->RightChild=0;
            Last=fp;
        }else{
            la=pre->LeftChild;
            while(la){pre=la;la=la->RightChild;}
            lt=pre;
            ///cout<<pre->Data<<endl;
            fp=pre->fa;
            fp->RightChild=0;
            Last=fp;
        }
    }
    Number--;
    return *this;
}
/*
    提取最小(最大)元素时，当cur位于小根层且出现cur的孙子节点比cur小（大）的并且交换后，由于不能保证在其父节点下面的层中的元素
一定比父节点小（大），故cur与其孙子节点交换后还仍需判断cur是否比其父节点大（小），如果比其父节点大（小），则交换cur和其父节点
*/
///提取堆中的最大元素
template<class T>
MaxMinHeap<T>& MaxMinHeap<T>::Extract_Max(T& x){
    ///如果堆为空
    if(!Top) {printf("Empty Error\n");return *this;}
    ///由于堆的根节点位于小根层，因而堆的最大值位于根节点的左右孩子中
    if(Top->LeftChild==0) {x=Top->Data;Top=Last=0;Number--;return *this;}
    else{
       ///Target是最大元素
       HeapNode<T>* Target;
       Target=Top->LeftChild;
       ///cout<<"top ---- "<<Top->Data<<endl;
       if(Top->RightChild&&Top->RightChild->Data>Top->LeftChild->Data) Target=Top->RightChild;
       x=Target->Data;
       HeapNode<T>* lt;
       ///cout<<Last->Data<<endl;
       ///获得堆中最后一个元素的位置存于lt中
       GetLast(lt);
       ///cout<<"lll "<<lt->Num<<endl;
       ///将最后一个元素放在刚刚提取的元素的位置上
       Target->Data=lt->Data;

       bool l=1,f=1;
       HeapNode<T> *cur=Target;
       int k;
       ///cout<<"aa "<<cur->Num<<endl;
       ///调整堆，使其重新成为最小最大堆
       while(l||f){
            k=cur->Num;
            while(k>1) k/=4;
            if(k==1){///cur在小根层
                f=l=1;
                if(cur->RightChild){///cur有两个孩子
                    HeapNode<T>* llc=cur->LeftChild->LeftChild;
                    HeapNode<T>* NextNode;
                    if(llc){///cur有孙子节点
                        NextNode=cur->LeftChild->RightChild;
                        if(NextNode&&NextNode->Data<llc->Data) llc=NextNode;

                        NextNode=cur->RightChild->LeftChild;
                        if(NextNode&&NextNode->Data<llc->Data) llc=NextNode;

                        NextNode=cur->RightChild->RightChild;
                        if(NextNode&&NextNode->Data<llc->Data) llc=NextNode;
                        ///原来的cur下移，需要重新判断
                        if(llc->Data<cur->Data) {
                            swap(cur,llc); cur=llc;
                        ///原来的cur下移后，需要判断cur是否比其父节点大，如果比父节点大，则与父节点交换
                            if(cur->Data>cur->fa->Data) {swap(cur,cur->fa);cur=cur->fa;}
                            continue;
                        }
                        f=l=0;
                    }else{///cur没有孙子节点
                        llc=cur->LeftChild;
                        if(cur->LeftChild->Data<cur->RightChild->Data) llc=cur->RightChild;
                        if(cur->Data>llc->Data) swap(cur,llc);
                        f=l=0;
                    }
                }else if(cur->LeftChild){///cur只有左孩子
                    if(cur->Data>cur->LeftChild->Data)
                        swap(cur,cur->LeftChild);
                    f=l=0;
                }else f=l=0;///cur没有孩子
            }else{///cur在大根层
                f=l=1;
                if(cur->RightChild){///cur有两个孩子
                    HeapNode<T>* llc=cur->LeftChild->LeftChild;
                    HeapNode<T>* NextNode;
                    if(llc){///cur有孙子节点
                        NextNode=cur->LeftChild->RightChild;
                        if(NextNode&&NextNode->Data>llc->Data) llc=NextNode;

                        NextNode=cur->RightChild->LeftChild;
                        if(NextNode&&NextNode->Data>llc->Data) llc=NextNode;

                        NextNode=cur->RightChild->RightChild;
                        if(NextNode&&NextNode->Data>llc->Data) llc=NextNode;
                        ///原来的cur下移，需要重新判断
                        if(llc->Data>cur->Data){
                            swap(cur,llc);cur=llc;
                            ///原来的cur下移后，需要判断cur是否比其父节点小，如果比父节点小，则与父节点交换
                            if(cur->Data<cur->fa->Data) {swap(cur,cur->fa);cur=cur->fa;}
                            continue;
                        }
                        f=l=0;
                    }else{///cur没有孙子节点
                        llc=cur->LeftChild;
                        if(cur->RightChild->Data>llc->Data) llc=cur->RightChild;
                        if(cur->Data<llc->Data) swap(cur,llc);
                        f=l=0;
                    }
                }else if(cur->LeftChild){///cur只有左孩子
                    if(cur->Data<cur->LeftChild->Data)
                        swap(cur,cur->LeftChild);
                    f=l=0;
                }else f=l=0;///cur没有孩子
            }
       }
       return *this;
    }
}

///提取堆中最小元素
template<class T>
MaxMinHeap<T>& MaxMinHeap<T>::Extract_Min(T& x){
    ///如果堆为空
    if(!Top){printf("Empty Error\n");return *this;}
    ///如果堆只有左孩子
    if(Top->LeftChild==0) {x=Top->Data;Top=Last=0;Number--;return *this;}
    else{
        x=Top->Data;
        HeapNode<T>* ln;
        ///找到堆中最后一个元素
        GetLast(ln);
        //cout<<"pp "<<ln->Data<<endl;

        Top->Data=ln->Data;
        bool f=1,l=1;
        HeapNode<T>* cur=Top;
        while(f||l){
            int k=cur->Num;
            while(k>1) k/=4;
            if(k==1){///cur在小根层
                f=l=1;
                HeapNode<T>* llc;
                ///如果cur有两个孩子
                if(cur->RightChild){
                    HeapNode<T>* NextNode=cur->LeftChild;
                    llc=NextNode->LeftChild;
                    if(llc){///如果cur有孙子节点
                        NextNode=cur->LeftChild->RightChild;
                        if(NextNode&&NextNode->Data<llc->Data) llc=NextNode;

                        NextNode=cur->RightChild->LeftChild;
                        if(NextNode&&NextNode->Data<llc->Data) llc=NextNode;

                        NextNode=cur->RightChild->RightChild;
                        if(NextNode&&NextNode->Data<llc->Data) llc=NextNode;
                        ///找到孙子节点中最小的元素，与cur比较，如果小于cur，cur与其交换
                        if(llc->Data<cur->Data){
                        ///交换cur和孙子节点
                            swap(cur,llc);cur=llc;
                        ///如果cur比父节点要大，则将cur与父节点交换
                            if(cur->Data>cur->fa->Data){swap(cur,cur->fa);cur=cur->fa;}
                            continue;
                        }
                        f=l=0;
                    }else{
                        ///如果cur没有孙子节点，则在其两个孩子中找到最大的一个，若其值比cur大，则与cur交换
                        if(cur->RightChild->Data<NextNode->Data) NextNode=cur->RightChild;
                        if(NextNode->Data<cur->Data) swap(cur,NextNode);
                        f=l=0;
                    }
                }else if(cur->LeftChild){///如果cur只有左孩子
                    if(cur->LeftChild->Data<cur->Data)
                        swap(cur,cur->LeftChild);
                    f=l=0;
                }else f=l=0;
            }else{
                f=l=1;
                HeapNode<T>* llc;
                if(cur->RightChild){///如果cur有两个孩子
                    llc=cur->LeftChild->LeftChild;
                    if(llc){///如果cur有孙子节点
                        HeapNode<T>* NextNode;

                        NextNode=cur->LeftChild->RightChild;
                        if(NextNode&&NextNode->Data>llc->Data) llc=NextNode;

                        NextNode=cur->RightChild->LeftChild;
                        if(NextNode&&NextNode->Data>llc->Data) llc=NextNode;

                        NextNode=cur->RightChild->RightChild;
                        if(NextNode&&NextNode->Data>llc->Data) llc=NextNode;
                        ///找到cur的最大的一个孙子节点，如果该节点比cur大，则与cur交换
                        if(llc->Data>cur->Data){
                            swap(cur,llc);cur=llc;
                            ///如果cur比父节点要小，则将cur与父节点交换
                            if(cur->Data<cur->fa->Data){swap(cur,cur->fa);cur=cur->fa;}
                            continue;
                        }
                        f=l=0;
                    }else{
                    ///如果cur没有孙子节点，则在其两个孩子中找到最大的一个，如过其值比cur大，则与cur交换
                        llc=cur->LeftChild;
                        if(cur->RightChild->Data>llc->Data) llc=cur->RightChild;
                        if(llc->Data>cur->Data) swap(cur,llc);
                        f=l=0;
                    }
                }else if(cur->LeftChild){
                ///如果cur只有左孩子
                    if(cur->LeftChild->Data>cur->Data) swap(cur,cur->LeftChild);
                    f=l=0;
                }else f=l=0;
            }
        }
        return *this;
    }
}

template<class T>
void MaxMinHeap<T>::levelorder(HeapNode<T>* rt){
    queue<HeapNode<T>* > que;
    que.push(rt);
    HeapNode<T>* l;
    while(!que.empty()){
        l=que.front();que.pop();
        visit(l);
        if(l->LeftChild) que.push(l->LeftChild);
        if(l->RightChild) que.push(l->RightChild);
    }
}

/*
    查找的原理：设x为堆中任一节点，如果x位于小根层，而且搜索的关键字比x小，则搜索的节点必定不在以x为根的子树中；
如果x位于大根层，而且搜索的关键字比x大，则搜索的节点必定不在以x为根的子树中；当x位于小根层，而搜索的关键字又比x大，
此时，如果关键字比x的孩子小，则与关键字相同的节点可能位于以x的孩子为根的子树中，因此将x的孩子加入队列que中，继续查找；
同理，当x位于大根层，且关键字右比x小，此时，如果关键字比x的孩子大，则与关键字相同的节点可能位于以x的孩子为根的子树中，因此
将x的孩子加入队列que中
*/
///查找学生信息
template<class T>
queue<T> MaxMinHeap<T>::Search(T& e){
    queue<HeapNode<T>* > que;///存放堆中的节点
    queue<T> qans;///存放与搜索关键字一致的节点的值
    ///如果堆为空
    if(Top==0) {cout<<"Empty Error"<<endl;return qans;}
    else{
        if(Top->Data==e) que.push(Top);
        ///若搜索关键字小于堆中最小的关键字
        else if(Top->Data>e){cout<<"No found such a student "<<endl;return qans;}
        ///判断搜索的关键字是否小于根节点的左孩子
        if(Top->LeftChild&&Top->LeftChild->Data>=e){
            que.push(Top->LeftChild);
        }
        ///判断搜索的关键字是否小于根节点的右孩子
        if(Top->RightChild&&Top->RightChild->Data>=e){
            que.push(Top->RightChild);
        }
    }

    map<int,int> mp;///记录已经入队的节点编号，避免重复加入
    int id=0;///map中元素个数
    int cnt=0;///与搜索关键字一致的节点的个数
    HeapNode<T>* Current;
    while(!que.empty()){
        Current=que.front();que.pop();
        if(Current->Data==e)
            ///如果此节点尚未入队，则将其入队保存
            if(!mp.count(Current->Num)){mp[Current->Num]=id++;qans.push(Current->Data);cnt++;}
        int k=Current->Num;
        while(k>1) k/=4;///判断current所处的层
        if(k==1){///current在最小层
            if(Current->Data>e) continue;
            ///判断搜索的关键字是否介于current和其左孩子之间
            if(Current->LeftChild&&Current->LeftChild->Data>=e) {que.push(Current->LeftChild);}
            ///判断搜索的关键字是否介于current和其右孩子之间
            if(Current->RightChild&&Current->RightChild->Data>=e) {que.push(Current->RightChild);}
        }else{///current在最大层
            if(Current->Data<e) continue;
            ///判断搜索的关键字是否介于current和其左孩子之间
            if(Current->LeftChild&&Current->LeftChild->Data<=e) {que.push(Current->LeftChild);}
            ///判断搜索的关键字是否介于current和其右孩子之间
            if(Current->RightChild&&Current->RightChild->Data<=e) {que.push(Current->RightChild);}
        }
    }
    ///输出结果
    return qans;
}
template<class T>
queue<T> MaxMinHeap<T>::ShowElement(){
    queue<HeapNode<T>* > que;///存放堆中的节点
    queue<T> qans;///存放与搜索关键字一致的节点的值
    ///如果堆为空

    if(Top==0) {cout<<"Empty Error"<<endl;return qans;}
    else{
         que.push(Top);
    }

    HeapNode<T>* Current;
    while(!que.empty()){

        Current=que.front();que.pop();
        qans.push(Current->Data);

        if(Current->LeftChild) {que.push(Current->LeftChild);}

        if(Current->RightChild) {que.push(Current->RightChild);}
    }
    return qans;
}
///测试heap的初始化
struct node {
    char *name;
    int StudentNumber;

};
ostream & operator<<(ostream &os,node i){
        os<<"name: "<<i.name<<' '<<"StudentNumber: "<<i.StudentNumber<<endl;
        return os;
}
template <class T>
void MaxMinHeap<T>::print(){
    levelorder(Top);
}



#endif // MAXMINHEAP_H_INCLUDED
