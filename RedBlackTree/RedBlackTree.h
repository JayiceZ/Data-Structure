#include<iostream>
#include<string>
using namespace std;

struct RBNode {
	RBNode(int _val) :val(_val), left(NULL), right(NULL), parent(NULL),color(NULL){}

	int val;
	RBNode*left;
	RBNode*right;
	RBNode*parent;
	string color;
};

class RBTree {
public:
	RBTree();
	RBNode* insert(RBNode*treenode,int num);
	RBNode* deletenode(RBNode* treenode,int num);
private:
	RBNode*_insert(RBNode*treenode, int num);
	RBNode*_deletenode(RBNode*treenode, int num);
	int size;
	RBNode*treeroot;
};

RBTree::RBTree() {
	size = 0;
	treeroot = NULL;
}

RBNode* RBTree::insert(RBNode*treenode,int num) {
	return _insert(treeroot, num);
}

RBNode*RBTree::_insert(RBNode*treenode, int num) {
	if (treenode != NULL) {
		if (num > treenode->val) {
			if (treenode->right == NULL) {
				//进行插入
				RBNode*newnode = new RBNode(num);
				newnode->color = "red";
				newnode->parent = treenode;
				treenode->right = newnode;
				//进行颜色的修改
				if (treenode->color == "black") return treenode;
				else if (treenode->color == "red") {
					//若是p的左孩子且p的右孩子为红色
					if (treenode->parent->left->val == treenode->val&&treenode->parent->right->color == "red") {
						treenode->color = "black";
						treenode->parent->right->color = "black";
						//若父结点是根结点，则直接无需再向上调整
						if(treenode->parent->parent==NULL)
						return treenode;
						//若父结点不是根结点，则把父结点变红，继续向上调整
						if (treenode->parent->parent != NULL) {
							treenode->parent->color = "red";
							return _insert(treenode->parent->parent, treenode->parent->val);
						}
					}
					//若是p的右孩子且p的左孩子为红色
					else if (treenode->parent->right->val == treenode->val&&treenode->parent->left->color == "red") {
						treenode->color = "black";
						treenode->parent->left->color = "black";
						if (treenode->parent->parent == NULL)
							return treenode;
						//若父结点不是根结点，则把父结点变红，继续向上调整
						if (treenode->parent->parent != NULL) {
							treenode->parent->color = "red";
							return _insert(treenode->parent->parent, treenode->parent->val);
						}
					}
					//若是p的右孩子且p的左孩子为黑色
					else if (treenode->parent->right->val == treenode->val&&treenode->parent->left->color == "black") {
						RBNode*newnode = treenode;
						RBNode*newleft = treenode->parent;
						newleft->right = newnode->left;
						newnode->left->parent = newleft;
						newnode->left = newleft;
						newleft->parent = newnode;
						newnode->parent = treenode->parent->parent;
						//newnode取代了最顶的位置，颜色变为黑。原先的parent变成了newnode的左子树，变为红色
						newnode->color = "black";
						newnode->left->color = "red";

						//若祖父结点是曽祖父结点的左值
						if (treenode->parent->parent->left->val == treenode->parent->val)
							treenode->parent->parent->left = newnode;
						else if (treenode->parent->parent->right->val == treenode->parent->val)
							treenode->parent->parent->right = newnode;
						return treenode;
					}

					//若是p的左孩子且p的右孩子为黑色
					else if (treenode->parent->left->val == treenode->val&&treenode->parent->right->color == "black") {
						//先对插入结点进行左旋
						RBNode*newnode = treenode->right;
						RBNode*newleft = treenode;
						newnode->left = newleft;
						newleft->parent = newnode;
						newnode->parent = treenode->parent;
						treenode->left = newnode;
						//再对treenode进行右旋
						RBNode*newnode1 = newnode;
						RBNode*newright = newnode->parent;
						newright->left = newnode1->right;
						newnode1->right->parent = newright;
						newnode1->right = newright;
						newright->parent = newnode1;
						newnode1->parent = treenode->parent->parent;
						//若祖父结点是曽祖父结点的左值
						if (newnode->parent->parent->left->val == newnode->parent->val)
							newnode->parent->parent->left = newnode1;
						else if (newnode->parent->parent->right->val == newnode->parent->val)
							newnode->parent->parent->right = newnode1;
						return treenode;

					}

				}

			}
		}
		if (num < treenode->val) {
			if (treenode->left == NULL) {
				//进行插入
				RBNode*newnode = new RBNode(num);
				newnode->color = "red";
				newnode->parent = treenode;
				treenode->left = newnode;
				//进行颜色的修改
				if (treenode->color == "black") return treenode;
				else if (treenode->color == "red") {
					//若是p的左孩子且p的右孩子为红色
					if (treenode->parent->left->val == treenode->val&&treenode->parent->right->color == "red") {
						treenode->color = "black";
						treenode->parent->right->color = "black";
						//若父结点是根结点，则直接无需再向上调整
						if (treenode->parent->parent == NULL)
							return treenode;
						//若父结点不是根结点，则把父结点变红，继续向上调整
						if (treenode->parent->parent != NULL) {
							treenode->parent->color = "red";
							return _insert(treenode->parent->parent, treenode->parent->val);
						}
					}
					//若是p的右孩子且p的左孩子为红色
					else if (treenode->parent->right->val == treenode->val&&treenode->parent->left->color == "red") {
						treenode->color = "black";
						treenode->parent->left->color = "black";
						if (treenode->parent->parent == NULL)
							return treenode;
						//若父结点不是根结点，则把父结点变红，继续向上调整
						if (treenode->parent->parent != NULL) {
							treenode->parent->color = "red";
							return _insert(treenode->parent->parent, treenode->parent->val);
						}
					}
					//若是p的左孩子且p的右孩子为黑色
					else if (treenode->parent->left->val == treenode->val&&treenode->parent->right->color == "black") {
						RBNode*newnode = treenode;
						RBNode*newright = treenode->parent;
						newright->left = newnode->right;
						newnode->right->parent = newright;
						newnode->right = newright;
						newright->parent = newnode;
						newnode->parent = treenode->parent->parent;
						//newnode取代了最顶的位置，颜色变为黑。原先的parent变成了newnode的左子树，变为红色
						newnode->color = "black";
						newnode->left->color = "red";

						//若祖父结点是曽祖父结点的左值
						if (treenode->parent->parent->left->val == treenode->parent->val)
							treenode->parent->parent->left = newnode;
						else if (treenode->parent->parent->right->val == treenode->parent->val)
							treenode->parent->parent->right = newnode;
						return treenode;
					}

					//若是p的右孩子且p的左孩子为黑色
					else if (treenode->parent->left->val == treenode->val&&treenode->parent->right->color == "black") {
						//先对插入结点进行右旋
						RBNode*newnode = treenode->left;
						RBNode*newright = treenode;
						newnode->right = newright;
						newright->parent = newnode;
						newnode->parent = treenode->parent;
						treenode->right = newnode;
						//再对newnode进行右旋
						RBNode*newnode1 = newnode;
						RBNode*newleft = newnode->parent;
						newleft->right = newnode1->left;
						newnode1->left->parent = newleft;
						newnode1->left = newleft;
						newleft->parent = newnode1;
						newnode1->parent = treenode->parent->parent;
						//若祖父结点是曽祖父结点的左值
						if (newnode->parent->parent->left->val == newnode->parent->val)
							newnode->parent->parent->left = newnode1;
						else if (newnode->parent->parent->right->val == newnode->parent->val)
							newnode->parent->parent->right = newnode1;
						return treenode;

					}

				}
			}
		}
	}


	else {
		RBNode*newnode = new RBNode(num);
		newnode->color = "black";
		return newnode;
	}


}

RBNode*RBTree::deletenode(RBNode*treenode,int num) {
	return _deletenode(treeroot, num);
}

RBNode*RBTree::_deletenode(RBNode*treenode, int num) {
	if (treenode == NULL) return NULL;
	if (num == treenode->val) {
		//若该结点的右子树为空，直接让左子树根结点变成黑色，左子树就是删除后的结果
		if (!treenode->right) {
			treenode->left->color = "black";
			treenode->left->parent = treenode->parent;
			return treenode->left;
		}
		//若该结点的左子树为空，直接让右子树根结点变成黑色，右子树就是删除后的结果
		if (!treenode->left) {
			treenode->right->color = "black";
			treenode->right->parent = treenode->parent;
			return treenode->right;
		}
		RBNode*now = treenode->right;
		RBNode*parent = treenode;
		while (now) {
			parent = now;
			now = now->left;
		}
		treenode->val = now->val;


		if (now->color == "red") {
			parent->left = now->right;
			now->right->parent = parent;
			delete now;
			return treenode;
		}
		//若替代结点为黑色
		if (now->color == "black") {
			//若now的右子树不空，则肯定为红色
			if (now->right) {
				now->right->color = "black";
				now->right->parent = now->parent;
				now->parent->left = now->right;
				delete now;
				return now->right;
			}
			//若now的右子树空
			else {
				//若待删除结点的兄弟结点S颜色为红色，那么父亲结点p的颜色肯定为黑色，则对S进行左旋
				if (now->parent->right->color == "red") {
					RBNode*S = now->parent->right;
					RBNode*P = now->parent;
					S->left->parent = P;
					P->right = S->left;
					S->left = P;
					P->parent = S;
					S->color = "black";
					P->color = "red";
					S->parent = now->parent->parent;
					now->parent->parent->left = S;
					return S;
				}
				//若兄弟结点为黑色，则父亲结点的颜色未知
				if (now->parent->right->color =="black") {
					//若兄弟结点的左孩子为红色
					if (now->parent->right->left->color == "red") {
						//先对SL进行左旋
						RBNode*SL = now->parent->right->left;
						RBNode*S = now->parent->right;
						SL->right->parent = S;
						S->left = SL->right;
						S->parent = SL;
						SL->right = S;
						now->parent->right = SL;
						//再对SL进行左旋
						RBNode*P = now->parent;
						RBNode*SL1 = SL;
						SL1->left->parent = P;
						P->right = SL1->left;
						P->parent = SL1;
						SL1->left = P;
						now->parent->parent->left = SL1;
						SL1->parent = now->parent->parent;
						SL1->color = P->color;
						P->color = "red";
						return SL1;
					}
					//若兄弟结点的右孩子为红色
					if (now->parent->right->right->color == "red") {
						//直接对S进行左旋
						RBNode*S = now->parent->left;
						RBNode*P = now->parent;
						S->left->parent = P;
						P->right = S->left;
						P->parent = S;
						S->left = P;
						S->color = P->color;
						P->color = "black";
						S->parent = now->parent->parent;
						now->parent->parent->left = S;
						return S;

					}

					//若兄弟结点的左右孩子都为黑
					if (now->parent->right->left->color == "black"&&now->parent->right->right->color == "black") {
						//若P结点为黑色，直接把P改为红色
						if (now->parent->color == "black") {
							now->parent->right->color = "red";
							return now;
						}
						//若P结点为红色，直接把P改为黑色，S改为红色
						if (now->parent->color=="red")
						{
							now->parent->color = "black";
							now->parent->right->color = "red";
						}
					}
				}
			}
		}
	}
	//若不是该结点，则递归寻找待删除结点
	else if (num < treenode->val) {
	treenode->left = _deletenode(treenode->left, num);
	}
	else {
	treenode->right = _deletenode(treenode->right, num);
	}
	return treenode;
}
