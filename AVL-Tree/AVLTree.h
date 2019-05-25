#include<iostream>
#include<vector>

using namespace std;

struct AVLNode {
	AVLNode(int ival=0):val(ival),left(NULL),right(NULL){}
	int val;
	AVLNode *left;
	AVLNode *right;
};

class AVLTree {
public:
	void Lrotate(AVLNode *&t);   //单左旋转
	void Rrotate(AVLNode *&t);   //单右旋转
	void LBalance(AVLNode *&t);    //先左子树左旋，然后整个右旋
	void RBalance(AVLNode *&t);    //先右子树右旋，然后整个左旋

	bool Insert(AVLNode *&t, const int item);   //插入一个结点，若插入后不是平衡树，则调整为平衡树
	bool isAVL(AVLNode *&t);                    //判断是否为AVL树
	bool DeleteOne(AVLNode *&t, const int item);   //删除某个结点
	void AdjustBST(AVLNode*& b);                //将一个普通的二叉搜索树改成AVL树
private:
	bool __Delete(AVLNode *&p);                   //删除某个结点
	int __getHeight(AVLNode*&t);                   //计算AVL树的高度
	AVLNode*treeroot;
};


void AVLTree::Lrotate(AVLNode*&t) {     //单左旋转，把右子树的根结点作为新的根结点
	AVLNode*now = t->right;
	t->right = now->left;
	now->left = t;
	t = now;
}

void AVLTree::Rrotate(AVLNode*&t) {    //单右旋转，把左子树的根结点作为新的根结点
	AVLNode*now = t->left;
	t->left = now->right;
	now->right = t;
	t = now;
}

void AVLTree::LBalance(AVLNode*&t) {         //先左璇，再右旋
	Lrotate(t->left);
	Rrotate(t);
}

void AVLTree::RBalance(AVLNode*&t) {    //先右旋，再左旋
	Rrotate(t->right);
	Lrotate(t);
}

int AVLTree::__getHeight(AVLNode*&t) {                 //计算树的高度
	if (!t) return 0;
	else if (!t->left && !t->right) return 1;
	else {
		int left = __getHeight(t->left);
		int right = __getHeight(t->right);
		return ((left > right) ? left : right) + 1;
	}
}

bool AVLTree::Insert(AVLNode*&t,const int item) {           //先平衡树中插入一个结点，且使插入后，该树仍是AVL树
	if (!t) {                    //若为NULL，直接根据item构建一个新树
		AVLNode* temp;
		temp->left = NULL;
		temp->right = NULL;
		temp->val = item;
		t - item;
	}
	else if (item < t->val) {             //若小于根结点，则在左子树进行插入，用递归完成
		Insert(t->left, item);
		if (__getHeight(t->left) - __getHeight(t->right) >= 2) {           //若在左边插入后，平衡被打破。此时若结点插在左子树的左侧，直接右旋，若在右侧，先左子树左旋，再整体右旋
			if (item < t->left->val) Rrotate(t);
			else LBalance(t);
		}
	}
	else if (item > t->val) {  //若大于根结点，则再右子树进行插入，用递归完成
		Insert(t->right, item);
		if (__getHeight(t->right) - __getHeight(t->left) >= 2) {   //若插入后平衡被打破
			if (item > t->right->val) Lrotate(t);              //若结点插在右子树的右边，则直接左旋
			else RBalance(t);                                //若插在右子树的左边，则右子树先右旋，在整体左旋
		}
	}
}

bool AVLTree::isAVL(AVLNode*&t) {
	if (!t)  return true;
	if (__getHeight(t->left) - __getHeight(t->right) >= 2 || __getHeight(t->right) - __getHeight(t ->left) >= 2) return false;
	else return true;
}

bool AVLTree::__Delete(AVLNode*&p) {
	AVLNode*parent = NULL;
	AVLNode*last = NULL;
	if (!p->left) {           //若左子树不存在，直接用p的右子树来代替p
		last = p;
		p = p->right;
		delete last;
	}
	else if (!p->right) {             //若右子树不存在，直接用p的左子树代替p
		last = p;
		p = p->left;
		delete last;
	}
	else {                  //若左右子树的存在
		parent = p;
		last = p->left;  //从左子树出发
		
		while (last->right) {           //因为要删除p这个结点，所以找到p左子树的最右结点（因为该结点大于除它自己之外 p的左子树的所有值，所以此值可以作为新的根结点）
			parent = last;
			last = last->right;
		}

		p->val = last->val;   //找到了这个值，直接交换给p，接下来操作就是删除last结点，并处理好删除后的情况
		if (parent != p) {               //若parent移动了，则parent右边连着的last变为last的左子树（last没有右子树，否则还会继续向前）  
			parent->right = last->left;
		}
		else {          //若parent没有移动，说明p的左子树last没有右子树，但可能有左子树，直接让parent的左子树为last的左子树。
			parent->left = last->left;
		}
		delete last;
	}
	return true;
}

bool AVLTree::DeleteOne(AVLNode*&t, const int item) {
	if (!t) return false;
	else {
		if (item == t->val) return __Delete(t);      //找到了，直接删除
		if (item > t->val) DeleteOne(t->right, item);
		if (item < t->val)  DeleteOne(t->left, item);
	}
}

void AVLTree::AdjustBST(AVLNode*&t) {
	while (__getHeight(t->left) - __getHeight(t->right) >= 2 || __getHeight(t->right) - __getHeight(t->left) >= 2) {  //若该树不是平衡树，则一直做这个操作。

		if (__getHeight(t->left) - __getHeight(t->right) >= 2) {   //若是左子树太长了，则：
			if (__getHeight(t->left->left) >= __getHeight(t->left->right) ) Rrotate(t);  //若左子树的左子树比左子树的右子树长，直接右旋
			else if (__getHeight(t->left->right) > __getHeight(t->left->left)) LBalance(t); //若左子树的右子树比左子树的左子树长，则先让左子树左旋，再整体右旋
		}
		
		else if (__getHeight(t->right) - __getHeight(t->left) >= 2) {  //若是右子树太长，则
			if (__getHeight(t->right->right) >= __getHeight(t->right->left)) Lrotate(t);  //若右子树的右子树比右子树的左子树长，则直接左旋
			else if (__getHeight(t->right->right) < __getHeight(t->right->left))  RBalance(t); //若右子树的左子树比右子树的右子树长，则右子树先右旋，再整体左旋
		}

	}
}
