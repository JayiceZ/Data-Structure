#include<iostream>
#include"stack.h"
#include<string>
#include<vector>
using namespace std;

int main(void) {
	/*测试构造函数
	*/
	stack sta1;
	sta1.print();
	vector<int> lis = { 1,2,3,4,5,6,7,8 };
	stack sta2(lis);
	cout << "利用数组构造成功，栈的内容为：";
	sta2.print();
	cout << "---------------------------------------------------" << endl << endl;

	/*测试功能函数
	*/

	//测试入栈操作
	cout << "在进行入栈操作前，栈的内容为：";
	sta2.print(); cout << endl;
	sta2.push(3);
	cout << "入栈操作成功，栈的内容为：";
	sta2.print(); cout << endl;

	cout << "在进行入栈操作前，栈的内容为：";
	sta2.print(); cout << endl;
	sta2.push(4);
	cout << "入栈操作成功，栈的内容为：";
	sta2.print(); cout << endl;
	cout << "------------------------------------------------------" << endl << endl;

	//测试出栈操作
	int val;
	if (!sta2.pop(val)) {
		cout << "入栈操作失败，该栈为空栈" << endl;
	}
	else {
		cout << "出栈成功，此时栈的内容为：";
		sta2.print(); cout << endl;
		cout << "出栈的元素为：" << val << endl;
	}

	if (!sta2.pop(val)) {
		cout << "入栈操作失败，该栈为空栈" << endl;
	}
	else {
		cout << "出栈成功，此时栈的内容为：";
		sta2.print(); cout << endl;
		cout << "出栈的元素为：" << val << endl;
	}
	cout << "---------------------------------------------" << endl << endl;




	//测试长度函数
	cout << "栈的内容为：";
	sta2.print();
	cout << "栈的长度为：" << sta2.length << endl;
	cout << "-----------------------------------------------" << endl << endl;


	
	//测试获取栈顶元素
	if (!sta2.top(val)) {
		cout << "获取失败，该栈为空栈" << endl;
	}
	else {
		cout << "该栈的栈顶元素为：" << val << endl;
		sta2.print();
	}
	cout << "----------------------------------------" << endl << endl;



	//测试清理函数
	sta2.clean();
	sta2.print();
	


	/*print()已经测试过，无需重复测试
	*/
}
