#include<iostream>
#include"List1.h"
#include<vector>
using namespace std;
int main(void){
	//测试构造函数
	List lis1;
	lis1.print();
	vector<int> array1={1,2,3,4,5,6,7,8};
	List lis2(array1);
	lis2.print();
	cout<<"lis2的长度为"<<lis2.length()<<endl;
	cout<<"--------------------------------------------------------"<<endl;
	
	//测试功能函数
	cout<<"操作之前，lis2的内容为：";
	lis2.print();
	if(lis2.insert(4,20)){
		cout<<"操作成功，lis2的内容变为：";
		lis2.print(); 
	}else{
		cout<<"位置2为不合法操作位置"<<endl;
	}
	
	cout<<"操作之前，lis2的内容为：";
	lis2.print();
	if(lis2.insert(2,10)){
		cout<<"操作成功，lis2的内容变为：";
		lis2.print(); 
	}else{
		cout<<"位置2为不合法操作位置"<<endl;
	}
	
	cout<<"操作之前，lis2的内容为：";
	lis2.print();
	if(lis2.insert(14,5)){
		cout<<"操作成功，lis2的内容变为：";
		lis2.print(); 
	}else{
		cout<<"位置14为不合法操作位置"<<endl;
	}
	
	//测试删除函数
	cout<<"操作之前，lis2的内容为:";
	lis2.print();
	int val;
	if(lis2.mydelete(2,val)) {
		cout<<"操作成功，lis2的内容变为：";
		lis2.print();
		cout<<"被删除的元素为："<<val<<endl;
		}else{
		cout<<"位置2为不合法操作位置"<<endl; 
	}
	
	cout<<"操作之前，lis2的内容为:";
	lis2.print();
	if(lis2.mydelete(1000,val)) {
		cout<<"操作成功，lis2的内容变为：";
		lis2.print();
		cout<<"被删除的元素为："<<val<<endl;
	}else{
		cout<<"位置1000为不合法操作位置"<<endl; 
	}
	
	//测试取值函数
	cout<<"操作之前，lis2的内容为:";
	lis2.print();
	if(lis2.getval(3,val)){
		cout<<"下标为3的内容为"<<val<<endl;}
	else{
		cout<<"搜索位置不合法"<<endl;
	}
	
	
		cout<<"操作之前，lis2的内容为:";
	lis2.print();
	if(lis2.getval(100,val)){
		cout<<"下标为3的内容为"<<val<<endl;}
	else{
		cout<<"搜索位置不合法"<<endl;
	}
	
	//测试求长度函数
	cout<<"操作之前，lis2的内容为:";
	lis2.print();
	cout<<lis2.length()<<endl; 
};
