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
private:
	int	find_pos(Node* node, int key);	//查找一个节点上key值合适插入的位置
	bool find_node(int key, getnode* search);	//寻找插入位置信息,返回false说明没有根节点
	bool _insert(Node* node, int key, int keypos, Node* child = 0);		//在一个节点的keys中添加键值
	bool split(Node* node, Node*& child);
	bool find_earse(int key, getnode* get);	//返回false查找不存在,
	bool get_ltree_rnode(Node* start, int keypos, Node*& res);	//得到keypos位置左子树最右节点
	int	 get_childpos(Node* parent, Node* child);
	Node* combine(Node* parent, Node* brother, Node* node, int parentKeyPos);	//返回合并之后的节点
	Node*root;
};


int BTree::find_pos(Node*node, int key) {
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
			else {

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


bool BTree::find_earse(int key, getnode*get) {
	Node*temp = root;
	int posi=1;
	while (true) {
		for (posi = 1; posi <= temp->keycount&&key < temp->key[posi]; posi++);
		//若找到了叶子结点，posi元素还是比key答案，则找不到
		if (temp->leaf&&temp->key[posi] > key) return false;
		//若for循环的中断是因为确切地找到了key值，则得到了该结点
		else if (temp->key[posi] == key) {
			get->node = temp;
			get->keypos = posi;
		}
		//若temp既不是叶子结点，在temp也找不到确切的key值，则说明key在temp的child[posi-1]上
		temp = temp->child[posi - 1];
	}
}

bool BTree::get_ltree_rnode(Node*start, int keypos,Node*&res) {
	if (start == NULL) return false;	
	start = start->child[keypos - 1];//   左子树
	while (!start->leaf) {
		start = start->child[start->keycount];//最右值
	}
	res = start;
	return true;
}

int BTree::get_childpos(Node*parent, Node*child) {
	for (int i = 0; i < parent->keycount; i++) {
		if (parent->child[i] == child) return i;
	}

	return -1;	
}

Node* BTree::combine(Node* parent, Node* brother, Node* node, int parentKeyPos) {
	int key = parent->key[parentKeyPos];
	for (int i = parentKeyPos; i < parent->keycount; i++) {
		parent->key[i] = parent->key[i + 1];
		parent->child[i] = parent->child[i + 1];
	}
	parent->keycount--;

	//父结点的parentKeyPos上的元素（即key）只有两种情况，要么比node的所有元素大（顺序node key brother），要么比brother的所有元素大（顺序brother key node）
	if (key > node->key[node->keycount]) {
		node->key[node->keycount + 1] = key;
		node->child[node->keycount + 1] = brother->child[0];
		node->keycount++;
	}
	else {
		brother->key[brother->keycount + 1] = key;
		brother->child[brother->keycount + 1] = node->child[0];
		brother->keycount++;
	}

	Node*merge = new Node(node->parent, node->leaf);
	//若node在key的右边
	if (node->key[1] > brother->key[brother->keycount]) {
		merge->child[0] = brother->child[0];
		for (int i = 1; i <=brother->keycount; i++) {
			merge->key[i] = brother->key[i];
			merge->child[i] = brother->child[i];
			if (!merge->leaf)  merge->child[i]->parent = merge;
		}
		for (int i = brother->keycount + 1; i <= node->keycount + brother->keycount; i++) {
			merge->key[i] = node->key[i - brother->keycount];
			merge->child[i] = node->child[i - brother->keycount];
			if (!merge->leaf) merge->child[i]->parent = merge;
		}
	}

	//若node在key的左边
	else if (brother->key[1] > node->key[node->keycount]) {
		for (int i = 1; i <= node->keycount; i++) {
			merge->key[i] = node->key[i];
			merge->child[i] = node->child[i];
			if (!merge->leaf)  merge->child[i]->parent = merge;
		}
		for (int i = node->keycount + 1; i <= brother->keycount + node->keycount; i++) {
			merge->key[i] = brother->key[i - node->keycount];
			merge->child[i] = brother->child[i - node->keycount];
			if (!merge->leaf) merge->child[i]->parent = merge;
		}
	}

	merge->keycount = node->keycount + brother->keycount;
	parent->child[parentKeyPos - 1] = merge;
	delete node;
	delete brother;
	return merge;

}


bool BTree::mydelete(int key) {
	if (this->root == NULL) return  false;

	getnode *get;
	//若找不到该元素
	if (this->find_earse(key, get) == false)  return false;
	Node*node = get->node;
	int posi = get->keypos;
	//若不是叶子结点，则用左子树的最右值来取带，再删除左子树最右值
	if (!node->leaf) {
		//
		Node*replace = NULL;
		this->get_ltree_rnode(node, posi, replace);
		node->key[posi] = replace->key[replace->keycount];
		node = replace;//赋值为node，后续则是对replace进行删除
		replace->keycount--;
	}
	else {
		for (int i = posi; i < node->keycount; i++) {
			node->key[i] = node->key[i + 1];
			node->child[i] = node->child[i + 1];
		}
		node->keycount--;
	}

	//对删除之后各结点的元素数量等情况进行处理
	while (true) {
		//若是根结点
		if (node->parent == NULL) {
			//若即是根结点，又是叶结点
			if (node->leaf) {
				root = NULL;
			}
			else {
				root = node->child[0];
				root->parent = NULL;
			}
			return true;
		}

		//若不是根结点
		else {
			//若删除后，结点元素个数小于（M+1）/2-1.
			if (node->keycount < KEY_MIN) {
				int posi = this->get_childpos(node->parent, node);
				auto parent = node->parent;

				//若有左兄弟，并且左兄弟的元素个数大于最小元素个数，则可以向左兄弟借一个
				if (posi > 0 && parent->child[posi - 1]->keycount> KEY_MIN) {
					auto leftbro = parent->child[posi - 1];
					for (int i = node->keycount + 1; i >=1; i--) {
						node->key[i] = node->key[i - 1];
						node->child[i] = node->child[i - 1];
					}
					node->key[1] = parent->key[posi];
					node->keycount++;
					node->child[0] = leftbro->child[leftbro->keycount];  //别忘了
					node->child[0]->parent = node;

					parent->key[posi] = leftbro->key[leftbro->keycount];
					leftbro->keycount--;
					return true;
				}

				//若存在右兄弟，且右兄弟的元素个数大于最小元素个数，则可以向右兄弟借一个
				else if (posi < parent->keycount&&parent->child[posi + 1]->keycount>KEY_MIN) {
					auto rightbro = parent->child[posi + 1];

					node->key[node->keycount + 1] = parent->key[posi + 1];
					node->keycount++;
					node->child[node->keycount] = rightbro->child[0];
					node->child[node->keycount]->parent = node;


					parent->key[posi + 1] = rightbro->key[0];

					//在rightbro中删除key[0]，因为它已经被移到parent上了
					for (int i = 1; i < rightbro->keycount; i++) {
						rightbro->key[i] = rightbro->key[i + 1];
						rightbro->child[i] = rightbro->child[i + 1];
					}
					rightbro->keycount--;
					return true;
				}


				//左右兄弟都无法给自己借元素
				else {
					//若有左兄弟
					Node*merge = NULL;
					if (posi > 0) {
						auto left = parent->child[posi - 1];
						merge=this->combine(parent, left, node, posi);
					}
					//若有右兄弟
					else if (posi < parent->keycount) {
						auto right = parent->child[posi + 1];
						merge = this->combine(parent, right, node, posi+1);
					}
					node = merge->parent;  //上溯
				}
			}

			//若删除之后B-Tree仍然平衡，则删除直接结束
			else {
				return true;
			}
		}
	}

	return true;
}
