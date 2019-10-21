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
		bool insert(const int posi,const int val);  //根据posi（位置）插入节点
		bool mydelete(const int posi,int &val);   //删除posi处的节点
		bool getval(const int posi,int &val);  //获得posi处的节点
		void print();  //输出整个链表
		int length();  //获取链表长度
		
		//析构函数
		~List(); 
		
	private:
		int size;
		ListNode *head;			
};

//构造函数，直接让长度为0，设置头部指针
List::List(){
	size=0;
	head= new ListNode(0);
}
//构造函数2，根据数组来初始化链表
List::List(const vector<int> &array){
	head=new ListNode(0);           //头部哑结点 
	ListNode *now=head;
	for(int i=0;i<array.size();i++){
		now->next=new ListNode(array[i]); //连接
		now=now->next;  //now永远位于链表末端，所以要跳转
	}
	size=array.size();  //长度即为数组长度
}

bool List::insert(const int posi,const int val){
	if(posi<0||posi>size){  //posi不合法
		return false;
	}else{
		ListNode *now=head;
		for(int i=0;i<posi;i++){ //找到posi的前一个节点
			now=now->next;
		}
		//插入的固定套路
		ListNode *temp=new ListNode(val);
		temp->next=now->next;
		now->next=temp;
		return true;
	}
}

bool List::mydelete(const int posi,int&val){
	if(posi<0||posi>=size){//若posi不合法
		return false;
	}else{
		ListNode *now=head;
		for(int i=0;i<posi;i++){ //找到posi的前一个节点
			now=now->next;
		}
		//删除的固定套路
		ListNode *temp=now->next;
		now->next=temp->next;
		
		val=temp->val;//拿到被删除节点的值（当然也可以不拿。但是功能就没那么完善）
		free(temp);
		size-=1;//长度--
		return true;
	}
}

bool List::getval(const int posi,int &val){
	if(posi<0||posi>=size){
		return false;
	}else{
		ListNode*now=head->next;//注意这里取了now为链表的第一个节点，而不是头部哑结点，当然也可以取头部哑结点，但是下面的for循环条件要变成<=posi,反正目的是跳到posi位置，而之前的那些是要跳到posi前一个
		for(int i=0;i<posi;i++){
			now=now->next;
		}//得到了结果
		val=now->val;
		return true;
	}
}

//输出
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
//获取长度，直接用size就可以
int List::length(){
	return size;
}
