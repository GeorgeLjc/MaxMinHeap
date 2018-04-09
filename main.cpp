#include <iostream>
#include <stdio.h>
#include "MaxMinHeap.h"
#include "DoubleEndPriorityQueue.h"
#define LL long long
using namespace std;
typedef class Student {
    public :
    char Name[105];///����
    LL StudentID;///ѧ��
    char Sex[5];///�Ա�
    int Age;///����
    double Score;///�ɼ�
}stt[45];
bool operator >(Student& x,Student& y){
    return x.Score>y.Score;
}
bool operator <(Student& x,Student& y){
    return x.Score<y.Score;
}
bool operator ==(Student& x,Student& y){
    return x.Score==y.Score;
}
bool operator >=(Student& x,Student& y){
    return x.Score>=y.Score;
}
bool operator <=(Student& x,Student& y){
    return x.Score<=y.Score;
}
ostream& operator <<(ostream& os,Student stu){
    os<<"Student Name: "<<stu.Name<<endl;
    os<<"Student ID: "<<stu.StudentID<<endl;
    os<<"Student Sex: "<<stu.Sex<<endl;
    os<<"Student Age: "<<stu.Age<<endl;
    os<<"Student Score: "<<stu.Score<<endl;
    return os;
}

DoubleEndPriorityQueue<Student> shp;

///��ӭģ��
void Welcome(){
    cout<<endl;
    cout<<"                * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
    int cnt=0;
    while(cnt++<6){
    if(cnt==2)
        cout<<"                * Welcome to the Student Infromation System *"<<endl;
    else if(cnt==4)
        cout<<"                *     Auther : Jicheng Li Version : 2.10    *"<<endl;
    else
        cout<<"                *                                           *"<<endl;;
    }
    cout<<"                * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
    cout<<"��Enter������...."<<endl;
    getchar();
}

///�ѵĳ�ʼ��
void CreatHeap(){
    freopen("Data.txt","r",stdin);///�ض������뵽�ı��ļ�
    int total;
    cin>>total;

    int ii=1;
    while(ii<=total){
        Student stu;
        scanf("%s",stu.Name);

        scanf("%I64d",&stu.StudentID);

        scanf("%s",stu.Sex);

        scanf("%d",&stu.Age);

        scanf("%lf",&stu.Score);

        ii++;

        shp.Insert(stu);
    }
    fclose(stdin);
}

bool IsEmpty(){
    if(shp.IsEmpty()){
        cout<<"\nEmpty Error"<<endl;
        return 1;
    }else return 0;
}

///ѡ��ģ��
void choose(){
    int choice=1;
    while(choice){
        system("cls");
        cout<<"\n- - - - - - - - - - - - - - - - - - - - - - - - "<<endl;
        cout<<"*  �����룺\n*  1�����ݳɼ���ѯѧ����Ϣ\n*  2����ѯ��߷�ѧ����Ϣ\n*  3����ѯ��ͷ�ѧ����Ϣ\n*  4��ɾ����߷�ѧ����Ϣ\n*  5��ɾ����ͷ�ѧ����Ϣ\n*  6������ѧ����Ϣ\n*  0���˳�"<<endl;
        cout<<"- - - - - - - - - - - - - - - - - - - - - - - -\n"<<endl;
        scanf("%d",&choice);
        bool con=0;
        switch(choice){
            case 1:{
                double testscore;
                cout<<"������ɼ���"<<endl;
                //cout<<'a'<<endl;
                scanf("%lf",&testscore);

                if(IsEmpty()) return ;
                Student test=(Student){"test1",100066,"M ",15,testscore};
                queue<Student> que=shp.Search(test);
                if(que.empty()) cout<<"ϵͳ��û�и÷�����ѧ��\n"<<endl;
                else{
                    while(!que.empty()){
                        Student stu=que.front();que.pop();
                        cout<<stu<<endl;
                    }
                }
                cout<<"��Enter������...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 2:{
                if(IsEmpty()) return ;
                Student stu;
                shp.Max(stu);
                queue<Student> que=shp.Search(stu);
                //cout<<stu<<endl;
                cout<<"             + + + + + + + + + + + + + + + +"<<endl;
                cout<<"             +           ��ѯ���          +"<<endl;
                cout<<"             + + + + + + + + + + + + + + + +\n"<<endl;
                cout<<"\n";
                while(!que.empty()){
                    stu=que.front();que.pop();
                    cout<<stu<<endl;
                }
                cout<<"��Enter������...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 3:{
                if(IsEmpty()) return ;
                Student stu;
                shp.Min(stu);
                queue<Student> que=shp.Search(stu);
                cout<<"             + + + + + + + + + + + + + + + +"<<endl;
                cout<<"             +           ��ѯ���          +"<<endl;
                cout<<"             + + + + + + + + + + + + + + + +\n"<<endl;
                cout<<"\n";
                while(!que.empty()){
                    stu=que.front();que.pop();
                    cout<<stu<<endl;
                }
                cout<<"��Enter������...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 4:{
                Student stu;
                shp.Extract_Max(stu);
                cout<<"��߷�ѧ����Ϣ�Ѿ���ϵͳ��ɾ��"<<endl;
                cout<<"��Enter������...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 5:{
                Student stu;
                shp.Extract_Min(stu);
                cout<<"��ͷ�ѧ����Ϣ�Ѿ���ϵͳ��ɾ��"<<endl;
                cout<<"��Enter������...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 6:{
                Student stu;
                cout<<"\n������ѧ������"<<endl;
                cin>>stu.Name;
                cout<<"\n������ѧ��ѧ��"<<endl;
                cin>>stu.StudentID;
                cout<<"\n������ѧ���Ա�"<<endl;
                cin>>stu.Sex;
                cout<<"\n������ѧ������"<<endl;
                cin>>stu.Age;
                cout<<"\n������ѧ���ɼ�"<<endl;
                cin>>stu.Score;
                shp.Insert(stu);
                cout<<"\n�ɹ����ѧ��\n"<<endl;
                cout<<"��Enter������...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 0:{
                cout<<"\n��л��ʹ�ñ�ϵͳ\n"<<endl;
                break;
            }

            default:{
                cout<<"\n����ѡ�������ѡ��\n"<<endl;
                con=1;
                cout<<"��Enter������...."<<endl;
                getchar();
                getchar();
                break;
            }
        }
        if(con) continue;
    }
}

int main()
{
    Welcome();

    CreatHeap();

    freopen("CON", "r", stdin);///�ض������뵽����̨

    choose();

    return 0;
}
