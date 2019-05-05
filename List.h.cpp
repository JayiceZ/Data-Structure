#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct ListNode{
	ListNode(int ival=0):val(ival),next(NULL){
	}
	int val;
	ListNode*next;
};

class List{
	public:
		//默认构造函数
		List();
		List(const vector<int> &array);
		
		//功能函数
		bool insert(const int posi,const int val);
		bool mydelete(const int posi,int &val);
		bool getval(const int posi,int &val);
		void print();
		int length();
		
		//析构函数
		~List(); 
		
	private:
		int size;
		ListNode *head;			
};

List::List(){
	size=0;
	head= new ListNode(0);
}

List::List(const vector<int> &array){
	head=new ListNode(0);           //头部哑结点 
	ListNode *now=head;
	for(int i=0;i<array.size();i++){
		now->next=new ListNode(array[i]);
		now=now->next;
	}
	size=array.size();
}

bool List::insert(const int posi,const int val){
	if(posi<0||posi>size){
		return false;
	}else{
		ListNode *now=head;
		for(int i=0;i<posi;i++){
			now=now->next;
		}
		ListNode *temp=new ListNode(val);
		temp->next=now->next;
		now->next=temp;
		return true;
	}
}

bool List::mydelete(const int posi,int&val){
	if(posi<0||posi>=size){
		return false;
	}else{
		ListNode *now=head;
		for(int i=0;i<posi;i++){
			now=now->next;
		}ListNode *temp=now->next;
		now->next=temp->next;
		val=temp->val;
		free(temp);
		size-=1;
		return true;
	}
}

bool List::getval(const int posi,int &val){
	if(posi<0||posi>=size){
		return false;
	}else{
		ListNode*now=head->next;
		for(int i=0;i<posi;i++){
			now=now->next;
		}val=now->val;
		return true;
	}
}

void List::print(){
	ListNode*now=head->next;
	while(now){
		if(now==head->next){
			cout<<now->val;
		}else{
			cout<<"->"<<now->val;
		}
		now=now->next;
	}cout<<endl;
}

int List::length(){
	return size;
}
