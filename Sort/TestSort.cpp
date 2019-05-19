#include"sort.h"
#include<iostream>
#include<string>
using namespace std;
int main(void) {
	sort sort;
	
	//测试冒泡排序
	int lis1[] = { 9,8,7,6,5,4,3,2,1 };
	int lis2[] = { 1 };
	cout << "lis1冒泡排序后的结果是：";
	sort.bubble_sort(lis1, 9);
	for (int i = 0; i < 9; i++) {
		cout << lis1[i] << " ";
	}
	cout << endl;

	cout << "lis2冒泡排序后的结果是：";
	sort.bubble_sort(lis2, 1);
	for (int i = 0; i < 1; i++) {
		cout << lis2[i] << " ";
	}
	cout << endl<<"---------------------------------------------------"<<endl;

	//测试插入排序
	int lis3[] = { 9,8,7,6,5,4,3,2,1 };
	int lis4[] = { 1 };
	cout << "lis3插入排序后的结果是：";
	sort.insert_sort(lis3, 9);
	for (int i = 0; i < 9; i++) {
		cout << lis3[i] << " ";
	}
	cout << endl;

	cout << "lis4插入排序后的结果是：";
	sort.insert_sort(lis4, 1);
	for (int i = 0; i < 1; i++) {
		cout << lis4[i] << " ";
	}
	cout << endl << "---------------------------------------------------" << endl;

	//测试选择排序
	int lis5[] = { 9,8,7,6,5,4,3,2,1 };
	int lis6[] = { 1 };
	cout << "lis5选择排序后的结果是：";
	sort.select_sort(lis5, 9);
	for (int i = 0; i < 9; i++) {
		cout << lis5[i] << " ";
	}
	cout << endl;

	cout << "lis6选择排序后的结果是：";
	sort.select_sort(lis6,1);
	for (int i = 0; i < 1; i++) {
		cout << lis6[i] << " ";
	}
	cout << endl << "---------------------------------------------------" << endl;

	//测试归并排序
	int lis7[] = { 9,8,7,6,5,4,3,2,1 };
	int lis8[] = { 1 };
	cout << "lis7归并排序后的结果是：";
	sort.merge_sort(lis7, 9);
	for (int i = 0; i < 9; i++) {
		cout << lis7[i] << " ";
	}
	cout << endl;

	cout << "lis8归并排序后的结果是：";
	sort.merge_sort(lis8, 1);
	for (int i = 0; i < 1; i++) {
		cout << lis8[i] << " ";
	}
	cout << endl << "---------------------------------------------------" << endl;

	//测试快速排序
	int lis9[] = { 9,8,7,6,5,4,3,2,1 };
	int lis10[] = { 1 };
	cout << "lis9快速排序后的结果是：";
	sort.quick_sort(lis9, 9);
	for (int i = 0; i < 9; i++) {
		cout << lis9[i] << " ";
	}
	cout << endl;

	cout << "lis10快速排序后的结果是：";
	sort.quick_sort(lis10, 1);
	for (int i = 0; i < 1; i++) {
		cout << lis10[i] << " ";
	}
	cout << endl << "---------------------------------------------------" << endl;

	//测试快速排序2
	/*int lis11[] = { 9,8,7,6,5,4,3,2,1 };
	int lis12[] = { 1 };
	cout << "lis5快速排序2后的结果是：";
	sort.quick_sort2(lis11, 9);
	for (int i = 0; i < 9; i++) {
		cout << lis11[i] << " ";
	}
	cout << endl;

	cout << "lis12快速排序2后的结果是：";
	sort.quick_sort2(lis12, 1);
	for (int i = 0; i < 1; i++) {
		cout << lis12[i] << " ";
	}
	cout << endl << "---------------------------------------------------" << endl;*/

	//测试希尔排序
	int lis13[] = { 9,8,7,6,5,4,3,2,1 };
	int lis14[] = { 1 };
	cout << "lis13希尔排序后的结果是：";
	sort.shell_sort(lis13, 9);
	for (int i = 0; i < 9; i++) {
		cout << lis13[i] << " ";
	}
	cout << endl;

	cout << "lis14希尔排序后的结果是：";
	sort.shell_sort(lis14, 1);
	for (int i = 0; i < 1; i++) {
		cout << lis14[i] << " ";
	}
	cout << endl << "---------------------------------------------------" << endl;
	system("pause");
}
