#include<iostream>
#include"newTree.h"
using namespace std;
void print(vector<int> &lis) {
	for (int i = 0; i < lis.size(); i++) {
		cout << lis[i] << " ";
	}
}
int main(void) {
	//测试构造函数
	vector<int> preorder = { 12,4,2,1,8,6,10,16,14,17 };
	vector<int> inorder = { 1,2,4,6,8,10,12,14,16,17 };
	Tree tree1(inorder, preorder);
	
	//测试遍历函数
	cout << "前序遍历是：";
	vector<int> a = tree1.preorder();
	print(a);
	cout << endl;

	cout << "中序遍历是：";
	vector<int> b = tree1.inorder();
	print(b);
	cout << endl;

	cout << "后序遍历是：";
	vector<int> c = tree1.postorder();
	print(c);
	cout << endl;

	cout << "层序遍历是：";
	vector<int> d = tree1.levelorder();
	print(d);
	cout << endl;
	cout << "-------------------------------------------------" << endl << endl;
}
