#include<iostream>
#include"tree.h"
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

	//测试插入删除函数
	cout << "tree1的中序遍历结果是";
	vector<int> e = tree1.inorder();
	print(e);

	tree1.insert(15);
	cout <<endl<< "插入15" << endl << endl;

	cout << "tree1的中序遍历结果是";
	vector<int> f = tree1.inorder();
	print(f);
	cout << endl<<"----------------------------------------" << endl << endl;

	tree1.mydelete(15);
	cout <<endl<< "删除15" << endl << endl;;

	cout << "tree1的中序遍历结果是";
	vector<int> g = tree1.inorder();
	print(g);

	//测试深度函数
	cout << endl<<"tree1的深度是" << tree1.depth() << endl;


	//测试寻找公共父节点函数
	cout << "tree1的中序遍历结果是";
	vector<int> h = tree1.inorder();
	print(h);
	cout << endl;
	cout << "14 与 17的公共父节点是：" << tree1.findparent(14,17)->val << endl;
	cout << "------------------------------------------" << endl;

	//测试尺寸函数
	cout << "tree1的尺寸是：" << tree1.size() << endl;
	cout << "--------------------------------------------------" << endl;
	system("pause");
}
