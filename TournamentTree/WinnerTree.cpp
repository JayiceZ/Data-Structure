#include"forest.h"
#include<iostream>
#include<string>
#include<vector>


using namespace std;

class WinnerTree {
public:
	WinnerTree();   
	TreeNode* createTree(forest f);    //构造赢者树
private:
	TreeNode*treeroot;
};

WinnerTree::WinnerTree() {
	treeroot = NULL;

}

TreeNode* WinnerTree::createTree(forest f) {
	forest f2;
	//若只有一个选手，则胜者就是该选手
	if (f.length() <= 1) {
		return f.pop();
	}

	//若选手个数为奇数，则无法进行两两配对竞赛，即先在前两个选手之间决出胜负,胜利者参与到比赛中
	if (f.length() % 2 != 0) {
		TreeNode*num1 = f.pop();
		TreeNode*num2 = f.pop();
		TreeNode*newone = new TreeNode((num1->val > num2->val) ? num1->val : num2->val);
		newone->left = num1;
		newone->right = num2;
		f.insert(newone);

	}

	//两两进行比赛，把赛果作为新的forest。递归决出最后的冠军
	if (f.length() % 2 == 0) {
		while (f.length()) {
			TreeNode*comp1 = f.pop();
			TreeNode*comp2 = f.pop();
			TreeNode*newtree = new TreeNode((comp1->val > comp2->val) ? comp1->val : comp2->val);
			newtree->left = comp1;
			newtree->right = comp2;
			f2.insert(newtree);
		}
	}
	TreeNode*res = createTree(f2);
	return res;
}
