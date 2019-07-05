#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct TreeNode
{
	TreeNode(int _val) :val(_val), left(NULL), right(NULL){

	}
	int val;
	TreeNode *left;
	TreeNode *right;
};

struct ListNode
{
	ListNode(TreeNode* _node) :tree(_node), next(NULL) {

	}
		TreeNode*tree;
		ListNode*next;
};

class forest {
public:
	//constructor
	forest();

	void insert(TreeNode *root);       //向森林中插入一棵树，并保持森林的有序性（从上往下为从小到大）
	TreeNode* pop();                   //从森林中弹出最小的一棵树
	int length();                      //返回森林中的树的数量

private:
	ListNode*head;
	int size;
};

forest::forest() {
	head = new ListNode(NULL);
	size = 0;
}

void  forest::insert(TreeNode *root) {
	size += 1;
	if (root==NULL) {
		ListNode *newnode = new ListNode(root);
		newnode->next = head->next;
		head->next = newnode;
		return;
	}
	else {
		ListNode *now = head->next;
		ListNode *pre = head;

		while (now) {
			if (now->tree->val >= root->val) {
				break;
			}
			else {
				pre = now;
				now = now->next;
			}
		}
		ListNode *newnode = new ListNode(root);
		newnode->next = now;
		pre->next = newnode;
		return;
	}
}


TreeNode* forest::pop() {
	if (head->next == NULL) {
		return NULL;
	}
	else
	{
		ListNode*temp = head->next;
		TreeNode*res = head->next->tree;
		head->next = head->next->next;
		delete temp;
		size -= 1;
		return res;
	}
}

int forest::length() {
	return size;
}
