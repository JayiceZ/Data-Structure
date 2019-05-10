#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct ListNode {
	ListNode(int ival = 0) :val(ival), next(NULL) {
	}
	int val;
	ListNode *next;
};

class stack {
public:
	//构造函数
	stack();
	stack(const vector<int> &array);  //利用数组构造栈

	//功能函数
	void push(int val);  //入栈操作
	bool pop(int &val);  //出栈操作
	bool top(int &val);  //获取栈顶元素
	int length();
	void print();
	void clean();

private:
	ListNode *head;
	int size;
};

stack::stack() {
	head = NULL;
	size = 0;
}

//利用数组建立栈
stack::stack(const vector<int> &array) {
	if(!array.size()){
		head = NULL;
		size = 0;
	}
	else {
		head = new ListNode(array[array.size() - 1]);
		ListNode *now = head;
		for (int i = array.size() - 2; i >= 0; i--) {
			now->next = new ListNode(array[i]);
			now = now->next;
		}
		size = array.size();
	}
}

//入栈操作
void stack::push(int val) {
	ListNode *pushed =new ListNode(val);
	pushed->next=head;
	head = pushed;
	size += 1;
}

//出栈操作
bool stack::pop(int &val) {
	if (!head)  return false;
	else {
		ListNode *temp = head;
		val = temp->val;
		head = head->next;
		delete temp;
		size -= 1;
		return true;
	}
}

//获取栈顶元素
bool stack::top(int &val) {
	if (!head) return false;
	else {
		val = head->val;
		return true;
	}
}

//获取栈长度
int stack::length() {
	return size;
}

//输入栈的内容
void stack::print() {
	ListNode *now = head;
	while (now) {
		if (now == head) cout << now->val;
		else {
			cout << "-<" << now->val;
		}
		now = now->next;
	}cout << endl;
}


//清空函数
void stack::clean() {
	ListNode *now = head;
	while (now) {
		ListNode *temp = now;
		now = now->next;
		delete temp;
	}
	size = 0;
	head = NULL;
}
