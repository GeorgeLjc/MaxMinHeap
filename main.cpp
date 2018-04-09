#include <iostream>
#include <stdio.h>
#include "MaxMinHeap.h"
#include "DoubleEndPriorityQueue.h"
#define LL long long
using namespace std;
typedef class Student {
    public :
    char Name[105];///姓名
    LL StudentID;///学号
    char Sex[5];///性别
    int Age;///年龄
    double Score;///成绩
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

///欢迎模块
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
    cout<<"按Enter建继续...."<<endl;
    getchar();
}

///堆的初始化
void CreatHeap(){
    freopen("Data.txt","r",stdin);///重定向输入到文本文件
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

///选择模块
void choose(){
    int choice=1;
    while(choice){
        system("cls");
        cout<<"\n- - - - - - - - - - - - - - - - - - - - - - - - "<<endl;
        cout<<"*  请输入：\n*  1：根据成绩查询学生信息\n*  2：查询最高分学生信息\n*  3：查询最低分学生信息\n*  4：删除最高分学生信息\n*  5：删除最低分学生信息\n*  6：插入学生信息\n*  0：退出"<<endl;
        cout<<"- - - - - - - - - - - - - - - - - - - - - - - -\n"<<endl;
        scanf("%d",&choice);
        bool con=0;
        switch(choice){
            case 1:{
                double testscore;
                cout<<"请输入成绩："<<endl;
                //cout<<'a'<<endl;
                scanf("%lf",&testscore);

                if(IsEmpty()) return ;
                Student test=(Student){"test1",100066,"M ",15,testscore};
                queue<Student> que=shp.Search(test);
                if(que.empty()) cout<<"系统中没有该分数的学生\n"<<endl;
                else{
                    while(!que.empty()){
                        Student stu=que.front();que.pop();
                        cout<<stu<<endl;
                    }
                }
                cout<<"按Enter建继续...."<<endl;
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
                cout<<"             +           查询结果          +"<<endl;
                cout<<"             + + + + + + + + + + + + + + + +\n"<<endl;
                cout<<"\n";
                while(!que.empty()){
                    stu=que.front();que.pop();
                    cout<<stu<<endl;
                }
                cout<<"按Enter建继续...."<<endl;
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
                cout<<"             +           查询结果          +"<<endl;
                cout<<"             + + + + + + + + + + + + + + + +\n"<<endl;
                cout<<"\n";
                while(!que.empty()){
                    stu=que.front();que.pop();
                    cout<<stu<<endl;
                }
                cout<<"按Enter建继续...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 4:{
                Student stu;
                shp.Extract_Max(stu);
                cout<<"最高分学生信息已经从系统中删除"<<endl;
                cout<<"按Enter建继续...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 5:{
                Student stu;
                shp.Extract_Min(stu);
                cout<<"最低分学生信息已经从系统中删除"<<endl;
                cout<<"按Enter建继续...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 6:{
                Student stu;
                cout<<"\n请输入学生姓名"<<endl;
                cin>>stu.Name;
                cout<<"\n请输入学生学号"<<endl;
                cin>>stu.StudentID;
                cout<<"\n请输入学生性别"<<endl;
                cin>>stu.Sex;
                cout<<"\n请输入学生年龄"<<endl;
                cin>>stu.Age;
                cout<<"\n请输入学生成绩"<<endl;
                cin>>stu.Score;
                shp.Insert(stu);
                cout<<"\n成功添加学生\n"<<endl;
                cout<<"按Enter建继续...."<<endl;
                getchar();
                getchar();
                break;
            }
            case 0:{
                cout<<"\n感谢您使用本系统\n"<<endl;
                break;
            }

            default:{
                cout<<"\n错误选项，请重新选择\n"<<endl;
                con=1;
                cout<<"按Enter建继续...."<<endl;
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

    freopen("CON", "r", stdin);///重定向输入到控制台

    choose();

    return 0;
}
