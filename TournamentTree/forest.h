#include<iostream>

using namespace std;


struct TreeNode {
	TreeNode(int _val) :val(_val), left(NULL), right(NULL) {}
	int val;
	TreeNode *left;
	TreeNode *right;
};

struct ListNode {
	ListNode(TreeNode *_tree) :tree(_tree), next(NULL) {}

	TreeNode *tree;
	ListNode *next;
};


class forest {
public:

	forest();
	void insert(TreeNode *root);        //向森林中插入树
	TreeNode* pop();                    //从森林中弹出最近种下去的树（类似于栈）
	int length();                       //获取森林中树的个数
private:
	ListNode *head;
	int size;
};


forest::forest() {
	head = new ListNode(NULL);
	size = 0;
}

void forest::insert(TreeNode *root) {
	size++;
	ListNode *newnode = new ListNode(root);
	newnode->next = head->next;
	head->next = newnode;

}


TreeNode*forest::pop() {
	if (size == 0) {
		return NULL;
	}
	else {
		size--;
		ListNode *node = head->next;
		head->next = node->next;
		TreeNode*treenode = node->tree;
		delete node;
		return treenode;
	}
}

int forest::length() {
	return size;
}
