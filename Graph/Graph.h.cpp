#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<cstring>
#include<string>
#include<algorithm>
#include<queue>
using namespace std;

//无向图
class graph {
public:
	//构造函数
	graph();                //默认构造
	graph(int nsize);             //构造一个含nsize个结点的图，不包含任何边
	graph(vector<vector<int>> &lis);               //根据数组构建图
	graph(int *lis,int nsize);              //根据数组构造图

	//操作函数
	void print();

	vector<int> dfs(int startNode);           //深度优先遍历
	vector<int> bfs(int startNode);            //广度优先遍历

	vector<int> dijkstra(int startNode);           //dijkstra算法计算单源最短路径
	vector<int> floyd(int startNode);              //floyd算法计算多源（单源）最短路径

	graph prim();                             //prim算法构造最小生成树
	//graph kruskkal();                         //kruskkal算法构造最小生成树

private:
	int **data;
	int size;
};

//构造函数

graph::graph() {
	size = 0;
	data = NULL;
}

graph::graph(int nsize) {
	size = nsize;
	//申请空间
	data = new int*[size];
	for (int i = 0; i < size; i++) {
		data[i] = new int[size];
	}
	//构造size个结点，0条边
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j) data[i][j] = 0;
			else data[i][j] = -1;
		}
	}
	
}


graph::graph(vector<vector<int>> &lis) {
	size = lis.size();
	//申请空间
	data = new int*[size];
	for (int i = 0; i < size; i++) {
		data[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			data[i][j] = lis[i][j];
		}
	}
}


graph::graph(int *lis,int nsize) {
	size = nsize;

	data = new int*[size];
	for (int i = 0; i < size; i++) {
		data[i] = new int[size];
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			data[i][j] = lis[i*size + j];
		}
	}
}

//输入函数
void graph::print() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
cout << data[i][j] << " ";
		}cout << endl;
	}
}

//深度优先遍历
vector<int> graph::dfs(int start) {
	vector<int> record;
	if (!size || start < 0 || start >= size)
		return record;
	else {
		stack<int> sta;
		bool visit[10000];
		for (int i = 0; i < size; i++) {
			visit[i] = false;
		}
		sta.push(start);

		while (!sta.size()) {
			int temp = sta.top();
			sta.pop();
			//如果该结点已被访问，直接略过进入下一次循环
			if (visit[temp]) continue;
			else {
				record.push_back(temp);
				visit[temp] = true;
				for (int i = 0; i < size; i++) {
					if (data[temp][i] != -1 && !visit[i]) {
						sta.push(i);
					}
				}
			}

		}
	}
	return record;
}

//广度优先遍历(图的dfs和bfs之间的关系就如二叉树中的前序遍历与层序遍历)
vector<int> graph::bfs(int start) {
	vector<int> record;
	if (!size || start < 0 || start >= size) return record;

	queue<int> que;
	bool visit[10000];
	for (int i = 0; i < size; i++) {
		visit[i] = false;
	}
	que.push(start);

	while (que.size()) {
		int temp = que.front();
		que.pop();
		if (visit[temp]) continue;
		else {
			record.push_back(temp);
			visit[temp] = true;
			for (int i = 0; i < size; i++) {
				if (data[temp][i] != -1 && !visit[i]) {
					que.push(i);
				}
			}
		}
	}
	return record;
}

//最短路径：dijktra算法与floyd算法

vector<int> graph::dijkstra(int start) {
	vector<int> record;
	if (!size || start<0 || start>size) return record;

	bool visit[10000];
	for (int i = 0; i < size; i++) {
		visit[i] = false;
	}
	visit[start] = true;
	//构造dist数组，与start不连通的结点的dist设为无穷大，连通的结点的dist设为两点连线的权
	int dist[10000];
	for (int i = 0; i < size; i++) {
		if (data[start][i] == -1) dist[i] = INT_MAX;
		else dist[i] = data[start][i];
	}
	
	//寻找出当前dist最小的结点
	for(int u=0;u<size-1;u++){
		int posi, min = INT_MAX;
		for (int i = 0; i < size; i++) {
			if (!visit[i] && dist[i] < min) {
				min = dist[i];
				posi = i;
			}
		}

		visit[posi] = true;
		for (int j = 0; j < size; j++) {
			if (data[posi][j] != -1 && !visit[j]) {
				int temp = dist[posi] + data[posi][j];
				if (temp < dist[j]) dist[j] = temp;
			}
		}
	}
	
	for(int i = 0; i < size; i++){
		record.push_back(dist[i]);
	}
	return record;
}

vector<int> graph::floyd(int start) {
	vector<int> record;
	if (!size || start<0 || start>size) return record;

	int copy[1000][1000];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (data[i][j] == -1) copy[i][j] = INT_MAX;
			else copy[i][j] = data[i][j];
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				int temp = (copy[i][k] == INT_MAX || copy[j][k] == INT_MAX) ? INT_MAX : copy[i][k] + copy[k][j];
				if (temp < copy[i][j]) copy[i][j] = temp;
			}
		}
	}
	for (int i = 0; i < size; i++) {
		record.push_back(copy[start][i]);
	}
	return record;
}

//prim算法和kruskkal算法构造最小生成树

graph graph::prim() {
	if (!size) return(*this);

	int record[7][7];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (data[i][j] == -1) record[i][j] = -1;
			else record[i][j] = 0;
		}
	}

	int dist[7];
	int path[7];
	for (int i = 0; i < size; i++) {
		if (data[0][i] == -1) { dist[i] = INT_MAX;  path[i] = -1; }
		else {dist[i] = data[0][i]; path[i] = 0; }
	}
	bool visit[10000];
	for (int i = 0; i < size; i++) {
		visit[i] = false;;
	}
	visit[0] = true;

	//寻找与已知结点相连的最大结点
	for (int i = 0; i < size; i++) {
		int posi, pathway;
		int min = INT_MAX;
		for (int i = 0; i < size; i++) {
			if (!visit[i] && dist[i] < min) {
				min = dist[i];
				pathway = path[i];
				posi = i;
			}
		}

		visit[posi] = true;
		record[posi][pathway] = dist[posi];
		//更新所有结点到已知结点的最小值
		for(int i=0;i<size;i++){
			int temp = (data[posi][i] == -1) ? INT_MAX : data[posi][i];
			if (temp < dist[i]) {
				dist[i] = temp; path[i] = posi;
			}
		}
	}
	graph result((int*)record,size);
	return result;
}

