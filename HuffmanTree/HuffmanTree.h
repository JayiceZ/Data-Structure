#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <vector>
#include <queue>
#include "Forest.h"


using namespace std;


class HuffmanTree {
public:
	//constructor
	HuffmanTree(int leaves[], int size);  //根据数组，构造哈夫曼树

	map<int, string> HuffmanCode();   //获得哈夫曼编码

private:
	TreeNode*treeroot;
};


HuffmanTree::HuffmanTree(int leaves[], int size) {
	forest forest;
	for (int i = 0; i < size; i++) {
		TreeNode *newtree = new TreeNode(leaves[i]);
		forest.insert(newtree);
	}

	while (forest.length > 1) {
		TreeNode*left = forest.pop();             //取出两个最小值
		TreeNode*right = forest.pop();

		TreeNode*newnode = new TreeNode(left->val + right->val);       //新结点，左子树和右子树分别是取出的两个最小树，这个树的值为两树之和。
		newnode->left = left;
		newnode->right = right;

		forest.insert(newnode);
	}
	treeroot = forest.pop();
}

map<int,string> HuffmanTree::HuffmanCode() {
	map<int, string> res;

	queue<pair<TreeNode*, string>> que;
	que.push(make_pair(treeroot, "0"));

	while (que.size()) {
		pair<TreeNode*, string> temp = que.front();
		que.pop();

		res[temp.first->val] = temp.second;

		if (temp.first->left) que.push(make_pair(temp.first->left, temp.second + "0"));   //若左子树存在，则左子树的哈夫曼编码为父树的编码+“0”；
		if(temp.first->right) que.push(make_pair(temp.first->left, temp.second + "1"));   ////若右子树存在，则右子树的哈夫曼编码为父树的编码+“1”；
	}
}
