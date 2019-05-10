#include<iostream>
#include<vector>
#include"Queue.h"
using namespace std;
int main(void) {
	//测试构造函数与入队函数
	queue q1;
	if (q1.insert(1)) cout << "数字1进队成功" <<endl;
	if (q1.insert(2)) cout << "数字2进队成功" << endl;
	if (q1.insert(3)) cout << "数字3进队成功" << endl;
	if (q1.insert(4)) cout << "数字4进队成功" << endl;
	if (q1.insert(5)) cout << "数字5进队成功" << endl;
	if (q1.insert(6)) cout << "数字6进队成功" << endl;
	cout << "此时队列的内容是：";
	q1.print();
	if (q1.insert(6)) cout << "数字6进队成功" << endl;
	cout << "此时队列的内容是：";
	q1.print();
	cout << endl<<"--------------------------------------------------" << endl;

	//测试出队函数
	if (q1.mydelete()) {
		cout << "出队成功，此时队列的内容是：";
		q1.print();
	}
	else {
		cout << "出队失败，q1为空栈" << endl;
	}
	queue q2;
	if (q2.mydelete()) {
		cout << "出队成功，此时队列的内容是：";
		q2.print();
	}
	else {
		cout << "出队失败，q2为空栈" << endl;
	}
	cout << "--------------------------------------------------" << endl;

	//测试长度函数
	cout << "q1此时队列的内容是：";
	q1.print();
	cout << "队列q1的长度为：" << q1.length() << endl;
	cout << "q2此时队列的内容是：";
	q2.print();
	cout << "队列q2的长度为：" << q2.length() << endl;
	cout << "--------------------------------------------------" << endl;

	//测试查找函数
	cout << "q1此时队列的内容是：";
	q1.print();
	cout << "数字5所在的位置为：" << q1.findval(5) << endl;
	cout << "--------------------------------------------------" << endl;


	//测试销毁函数与判断函数
	cout << "q1此时队列的内容是：";
	q1.print();
	if (q1.isempty()) cout << "该队列为空" << endl;
	else cout << "该队列非空" << endl;

	q1.destroy();
	cout << "q1此时队列的内容是：";
	q1.print();
	cout << "q1此时队列的内容是：";
	q1.print();
	cout << endl<< "--------------------------------------------------" << endl;



	system("pause");
}
