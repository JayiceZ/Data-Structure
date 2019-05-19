#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;
void  swap(int *a, int * b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

class sort {
public:
	void bubble_sort(int lis[], int size);
	void insert_sort(int lis[], int size);
	void select_sort(int lis[], int size);
	void merge_sort(int lis[], int size);
	void shell_sort(int lis[], int size);
	void quick_sort(int lis[], int size);
	void quick_sort2(int lis[], int size);
private:
	void __merge(int lis[], int begin,int end);
	void __quick(int lis[], int begin, int end);
	/*int __findmid(int lis[], int begin, int end);
	void __quick2(int lis[], int begin, int end);*/
};



//冒泡排序：思路较为简单，即遍历数组，每次把较大的数排到后一位
void sort::bubble_sort(int lis[], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = i+1; j < size; j++) {
			if (lis[i] > lis[j]) {
				int temp = lis[i];
				lis[i] = lis[j];
				lis[j] = temp;
			}
		}
	}
	return;
}


//插入排序：抽出一个数，在抽出之后的数组中找到一个合适的位置来存放该数
void sort::insert_sort(int lis[], int size) {
	for (int i = 0; i < size; i++) {
		int temp = lis[i];
		int ins = i - 1;
		while (ins >= 0 && lis[ins] > temp) {
			lis[ins + 1] = lis[ins];
			ins--;
		}
		lis[ins + 1] = temp;
	}
	return;
}



//选择排序：选择一个最小的数，排在数组的第一位，再在后面size-1长的数组中选出最小一个，放在次位
void sort::select_sort(int lis[], int size) {
	for (int i = 0; i < size; i++) {
		int min = lis[i];
		int posi = i;
		for (int j = i+1; j < size; j++) {
			if (lis[j] < min) {
				min = lis[j];
				posi = j;
			}
		}
		int temp = lis[posi];
		lis[posi] = lis[i];
		lis[i] = temp;
	}
	return;
}


//归并排序
void sort::merge_sort(int lis[], int size) {

	__merge(lis, 0, size - 1);
}

void sort::__merge(int lis[], int begin, int end) {
	if (begin >= end) return;

	int mid = (begin + end) / 2;
	__merge(lis, 0, mid);
	__merge(lis, mid + 1, end);

	vector<int> res;
	int posi1 = begin;
	int posi2 = mid + 1;

	while (posi1 <= mid && posi2 <= end) {
		if (lis[posi1] < lis[posi2]) {
			res.push_back(lis[posi1]);
			posi1++;
		}
		else {
			res.push_back(lis[posi2]);
			posi2++;
		}
	}

	while (posi1 <= mid) {
		res.push_back(lis[posi1]);
		posi1++;
	}

	while (posi2 <= end) {
		res.push_back(lis[posi2]);
		posi2++;
	}

	for (int i = begin,k=0; i <=end; i++,k++) {
		lis[i] = res[k];
	}
	return;
}

//快速排序
void sort::quick_sort(int lis[], int size) {
	__quick(lis, 0, size - 1);
	return;
}

void sort::__quick(int lis[], int begin, int end) {
	if (begin >= end) return;

	int mid = lis[begin];  //初始化令主元的位置位于数组头
	int lastposi = begin;      //lastposi为小于主元的最后一个元素

	for (int i = begin + 1; i <= end; i++) {
		if (lis[i] < mid) {
			lastposi++;
			swap(&lis[lastposi], &lis[i]);
		}
	}
		swap(&lis[lastposi], &lis[begin]);
		
		__quick(lis, begin, lastposi - 1);
		__quick(lis, lastposi + 1, end);
	return;
}


//快排法2
/*void sort::quick_sort2(int lis[], int size) {
	__quick2(lis, 0, size - 1);
	return;
}

void sort::__quick2(int lis[], int begin, int end) {
	int mid = __findmid(lis, begin, end);
	int posi1 = begin;
	int posi2 = end - 1;
	for (;;) {
		while (lis[++posi1] < mid) {}
		while (lis[--posi2] > mid) {}
		if (posi1 < posi2) swap(&lis[posi1], &lis[posi2]);
		else break;
	}
	swap(&lis[posi1], &lis[end - 1]);
	__quick2(lis, begin, posi1 - 1);
	__quick2(lis, posi1 + 1, end);
	return;
}

int sort::__findmid(int lis[], int begin, int end) {
	int mid = (begin + end) / 2;
	if (lis[begin] > lis[mid]) swap(&lis[begin], &lis[mid]);
	if (lis[begin] > lis[end]) swap(&lis[begin], &lis[end]);
	if (lis[mid] > lis[end]) swap(&lis[mid], &lis[end]);
	swap(&lis[mid], &lis[end - 1]);
	return lis[end-1];
}*/

//希尔排序
void sort::shell_sort(int lis[], int size) {
	int step = size / 2;


	while (step >= 1) {

		for (int i = 0; i < step; i++) {

			for (int j = i; j < size; j += step) {

				int temp = lis[j];
				int ins = j - step;
				while (ins >= 0 && lis[ins] > temp) {

					lis[ins + step] = lis[ins];
					ins = ins - step;

				}
				lis[ins + step] = temp;

			}

		}
		step /= 2;

	}
}
