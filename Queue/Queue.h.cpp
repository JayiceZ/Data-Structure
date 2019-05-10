#include<iostream>
#pragma once
#include<string>
#include<vector>
using namespace std;
struct ListNode {
	ListNode(int ival = 0) :val(ival), next(NULL) {

	}
	int val;
	ListNode*next;
};
class queue {
public:
	queue();
	bool insert(int val);
	bool mydelete();
	bool isempty();
	void print();
	int findval(int val);
	int length();
	void destroy();
private:
	ListNode *front;
	ListNode *rear;
};

queue::queue() {
	ListNode*p=new ListNode;
	p->val = 0;
	p->next = NULL;
	front = p;
	rear = p;
}

 bool queue::insert(int val) {
	ListNode*temp = new ListNode;
	temp->val = val;
	temp->next = NULL;
	rear->next = temp;
	rear = temp;
	return true;
}

 
 bool queue::mydelete() {
	 if (front == rear) {
		 return false;
	 }
	 else {
		 ListNode *temp = front->next;
		 front->next = temp->next;
		 free(temp);
		 return true;
	 }
}

 bool queue::isempty() {
	 if (rear==front) return true;
	 else return false;
}

 int queue::findval(int val) {
	 ListNode *temp = front->next;
	 int i = 1;
	 while (temp) {
		 if (temp->val == val) {
			 return i;
		 }
		 else {
			 i++;
			 temp = temp->next;
		 }
	 }return 0;
}

 int queue::length() {
	 if (front == rear) {
		 return 0;
	 }
	 else {
		 int i = 0;
		 ListNode*temp = front->next;
		 while (temp) {
			 i++;
			 temp = temp->next;
		 }
		 return i;
	 }
}

 void queue::destroy() {
	 while (true) {
		ListNode *temp = front->next;
		front->next = temp->next;
		if (front->next == NULL) break;
	 }rear = front;
 }

 void queue::print() {
	 vector<int> res;
	 ListNode*temp = front->next;
	 while (temp) {
		 res.push_back(temp->val);
		 temp = temp->next;
	 }
	 for (int i = 0; i < res.size(); i++) {
		 cout << res[i] << " ";
	 }
}
