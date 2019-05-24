/*
线索树，即指叶结点含有前驱后继的二叉树
而某个叶结点的前驱其实就是进行中序遍历时，上一个遍历到的结点
而后继则是进行中序遍历时下一个要遍历到的结点
特别注意前驱后继只存在于叶结点中
*/


#include<iostream>
#include<string>
#include<stack>
#include"标头.h"
using namespace std;

struct ThreadNode {
	ThreadNode(int ival = 0) :val(ival), left(NULL), right(NULL), lflag(0), rflag(0){}
	int val, lflag, rflag;
	ThreadNode*left;
	ThreadNode*right;
};

class ThreadTree{
public:
	ThreadTree();
	ThreadTree(Tree &lis);
	vector<int> inorder();
	vector<int> reinorder();

private:
	ThreadNode *__buildTree(TreeNode* root);
	ThreadNode*__getFirst(ThreadNode*root);
	ThreadNode*__getNext(ThreadNode*posi);
	ThreadNode*__getLast(ThreadNode*root);
	ThreadNode*__getPre(ThreadNode*posi);
	ThreadNode*treeroot;
};

ThreadNode *ThreadTree::__buildTree(TreeNode*root) {
	if (!root) return NULL;
	ThreadNode *temp = new ThreadNode(root->val);
	temp->right = __buildTree(root->right);
	temp->left = __buildTree(root->right);
	return temp;
}

ThreadTree::ThreadTree() {
	treeroot = NULL;
}

ThreadTree::ThreadTree(Tree &other) {
	treeroot = __buildTree(other.getroot());
	stack<ThreadNode*> sta;
	ThreadNode*now = treeroot;
	ThreadNode*pre = NULL;
	while (now) {          //像中序遍历一样进栈
		sta.push(now);
		now = now->left;
	}

	while (sta.size()) {
		ThreadNode *now = sta.top();
		sta.pop();
		ThreadNode*temp = now->right;
		while (temp) {
			sta.push(temp);
			temp = temp->left;
		}

		if (!now->left) {           //若结点左子树为空，则有前驱（除了最左边的），则前驱为pre，并把lflag标注为1，说明有前驱
			now->left = pre;
			now->lflag = 1;
		}

		if (!now->right) {
			if (!sta.size()) now->right = NULL;   //若栈空，则now为最右结点，无后继，所以为NULL。
			else now->right = sta.top();           //若栈不空，则后继为栈顶元素
			now->rflag = 1;
		}

		pre = now;           //更新前驱结点
	}
}

//获取中序遍历访问到的一个结点
ThreadNode* ThreadTree::__getFirst(ThreadNode*root) {
	ThreadNode *now = root;
	while (now&&now->lflag == 0) {                  //lflag为1证明无左子树，则为最左边
		now = now->left;
	}
	return now;
}

//获取中序遍历访问到的最后一个结点
ThreadNode* ThreadTree::__getLast(ThreadNode*root) {
	ThreadNode *now = root;
	while (now&&now->rflag == 0) {                  //rflag为1证明无右子树，则为最右边
		now = now->right;
	}
	return now;
}

//获取中序遍历访问某个结点前的的一个结点
ThreadNode* ThreadTree::__getPre(ThreadNode*posi) {
	if (posi->lflag == 0) return __getLast(posi->left);   //若左子树存在，则返回左子树最后一个遍历到的，因为是先遍历左子树再遍历结点posi
	else return posi->left;                               //若左子树不存在，则沿着posi的left可以找到其前驱，即前一个遍历的结点
}

ThreadNode*ThreadTree::__getNext(ThreadNode*posi) {
	if (posi->rflag == 0) return __getFirst(posi->right);  //若右子树存在，则返回右子树最后一个遍历到的，因为是先遍历结点，再遍历右子树                        
	else return posi->right;                          ////若右子树不存在，则沿着posi的right可以找到其前驱，即前一个遍历的结点
}


//利用线索树进行中序遍历
vector<int> ThreadTree::inorder() {
	vector<int> res;
	ThreadNode*now = __getFirst(treeroot);
	while (now) {
		res.push_back(now->val);
		now = __getNext(now);
	}
	return res;
}

//利用线索树进行反向中序遍历
vector<int> ThreadTree::inorder() {
	vector<int> res;
	ThreadNode*now = __getLast(treeroot);
	while (now) {
		res.push_back(now->val);
		now = __getPre(now);
	}
	return res;
}
