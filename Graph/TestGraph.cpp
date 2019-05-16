#include"graph.h"
#include<iostream>
using namespace std;
int main(void) {
	//测试构造函数
	graph g1;
	g1.print();
	cout << endl;

	vector<vector<int>> array = {
	{0,6,1,5,-1,-1},
	{6,0,5,-1,3,-1},
	{1,5,0,5,6,4},
	{5,-1,5,0,-1,2},
	{-1,3,6,-1,0,6},
	{-1,-1,4,2,6,0}
	};
	graph g2(array);
	g2.print();
	cout << endl;

	int array2[7][7]= {
	{0,6,1,5,-1,-1},
	{6,0,5,-1,3,-1},
	{1,5,0,5,6,4},
	{5,-1,5,0,-1,2},
	{-1,3,6,-1,0,6},
	{-1,-1,4,2,6,0}
	};
	graph g3((int *)array2, 7);
	g3.print();
	cout << endl;

	//测试深度优先遍与广度优先遍历
	cout << "g2的深度优先遍历结果是：";
	vector<int> res = g2.dfs(0);
	for (int i = 0; i < res.size(); i++) {
		cout << res[i] << " ";
	}
	cout << endl;

	cout << "g2的广度优先遍历结果是：";
	vector<int>res1 = g2.bfs(0);
	for (int i = 0; i < res1.size(); i++) {
		cout << res1[i] << " ";
	}
	cout << endl;

	//测试计算最短路径的两个算法：dijkstra算法与floyd算法

	cout << "使用dijkstra算法计算出最短路径：" << endl;
	res = g2.dijkstra(0);
	for (int i = 0; i < res.size(); i++) {
		cout << "结点" << i << "到结点0的最短路径dist是：" << res[i] << endl;
	}

	cout << "使用floyd算法计算出最短路径：" << endl;
	res = g2.floyd(0);
	for (int i = 0; i < res.size(); i++) {
		cout << "结点" << i << "到结点0的最短路径dist是：" << res[i] << endl;
	}

	//测试prim算法构建最小生成树
	cout << "利用prim算法，构建的最小生成树是：" << endl;
	graph tree = g3.prim();
	tree.print();
	system("pause");
}
