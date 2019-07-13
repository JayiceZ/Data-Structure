#include<iostream>
#include<string>
enum { M = 7, KEY_MIN = (M + 1) / 2 - 1, KEY_MAX = M - 1, KEY_START = 1, CHILD_MIN = (M + 1) / 2, CHILD_MAX = M };

using namespace std;

struct Node {
	Node(Node*p, bool flag = false) :parent(p), leaf(flag) {}
	bool leaf;
	int keycount;   //元素个数
	Node*parent;
	Node*child[M + 1];
	int key[M + 1];
};

struct getnode {
	getnode() :node(0), keypos(1) {}
	Node *node;   //指定结点
	int keypos;   //指定元素在指定结点中的位置
};

class BTree {
public:
	bool insert(int key);
	bool mydelete(int key);
	bool destroy();
private:
	int	find_pos(Node* node, int key);	//查找一个节点上key值合适插入的位置
	bool find_node(int key, getnode* search);	//寻找插入位置信息,返回false说明没有根节点
	bool _insert(Node* node, int key, int keypos, Node* child = 0);		//在一个节点的keys中添加键值
	bool split(Node* node, Node*& child);
	void _destroy(Node* node);
	bool find_earse(int key, getnode* eraseres);	//返回false查找不存在,
	bool get_ltree_rnode(Node* start, int keypos, Node*& res);	//得到keypos位置左子树最右节点
	int	 get_childpos(Node* parent, Node* child);
	Node* combine(Node* parent, Node* brother, Node* node, int parentKeyPos);	//返回合并之后的节点
	Node*root;
};


int BTree::find_pos(Node*node,int key) {
	if (node == NULL) {
		return -1;
	}

	int pos = 1;
	//找到key应该属于的区域
	for (; pos < node->keycount&&node->key[pos] < key; pos++);
	return pos;
}

bool BTree::find_node(int key, getnode*search) {
	if (root == NULL) {
		return false;
	}
	Node*temp = root;
	int posi = 0;
	while (!temp->leaf) {
		posi = find_pos(temp, key);
		temp = temp->child[posi - 1];
	}
	posi = find_pos(temp, key);
	if (search) {
		search->node = temp;
		search->keypos = posi;
	}
	return true;
}

bool BTree::_insert(Node* node, int key, int keypos, Node* child) {
	if (node == NULL && keypos < 1) {
		return false;
	}
	else
	{
		//向右移动，为插入点腾出位置
		for (int i = node->keycount + 1; i >= keypos; i--) {
			node->key[i] = node->key[i - 1];
			node->child[i] = node->child[i - 1];
		}
		//插入插入点
		node->key[keypos] = key;
		node->child[keypos - 1] = child;
		if (child) child->parent = node;
		return true;
	}
}

bool BTree::split(Node*node, Node*&child) {
	int posi = (M + 1) / 2;
	Node*left = new Node(node->parent, node->leaf);  //分裂出来的结点，父结点和原来的一样。
	child = left;
	left->child[0] = node->child[0];
	for (int i = 1; i < posi; i++) {
		left->key[i] = node->key[i];
		left->child[i] - node->child[i];
		if (left->child[i]) {
			left->child[i]->parent = left;
		}
		left->keycount++;
	}
	node->child[0] = node->child[posi];
	for (int i = posi + 1; i < M + 1; i++)
	{
		node->child[i - posi] = node->child[i];
		node->key[i - posi] = node->key[i];
	}
	node->keycount = node->keycount - posi;
	return true;
}

bool BTree::insert(int key) {
	getnode*res;
	if (this->find_node(key, res) == false) {
		root = new Node(NULL, true);
		res->node = root;
		res->keypos = 1;
	}
	Node*node = res->node;
	int posi = res->keypos;
	Node*child = NULL;
	while (node) {
		this->_insert(node, key, posi, child);
		node->keycount++;
		//若插入后元素个数越界
		if (node->keycount >= KEY_MAX) {
			this->split(node, child);

			//若node是根结点
			if (node->parent == NULL) {
				Node*newnode = new Node(NULL, false);
				newnode->key[KEY_START] = node->key[(M + 1) / 2];
				newnode->child[0] = child;
				newnode->child[1] = node;
				child->parent = newnode;
				node->parent = newnode;
				newnode->keycount++;
				this->root = newnode;
				break;
			}
			//若不是根结点，则把中间元素插入到父结点中
			else{

				node = node->parent;
				posi = this->find_pos(node, node->key[(M + 1) / 2]);
			}
		}
		//若不越界，插入直接成功
		else {
			break;
		}
	}
	return true;
}
