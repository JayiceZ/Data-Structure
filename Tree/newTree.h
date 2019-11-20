#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<queue>
using namespace std;
struct TreeNode {
	TreeNode(int ival = 0) :val(ival), left(NULL), right(NULL) {
	}
	int val;
	TreeNode *right;
	TreeNode *left;
};
class Tree {
public:
	Tree();
	Tree(vector<int>inorder, vector<int> preorder);
	Tree(vector<int> inorder, vector<int> postorder, int flag);
	vector<int> preorder();    // 非递归的前序遍历
	vector<int> inorder();
	vector<int> postorder();
	vector<int> postorder2();
	vector<int> levelorder();
	int size();

private:
	TreeNode *__buildTree1(vector<int> &inorder, vector<int> &preorder);
	TreeNode *__buildTree2(vector<int>&inorder, vector<int> &postorder);
	TreeNode *treeroot;
	int __size(TreeNode*root);
};

Tree::Tree() {
	treeroot = NULL;
}
Tree::Tree(vector<int> inorder, vector<int> preorder) {
	treeroot = __buildTree1(inorder, preorder);
}

TreeNode*Tree::__buildTree1(vector<int> &inorder, vector<int> &preorder) {
	if (!preorder.size() || !inorder.size()) {
		return NULL;
	}
	else {
		int rootval = preorder[0];
		TreeNode *root = new TreeNode(rootval);
		int dex;
		vector<int> left, right;
		for (int i = 0; i < inorder.size(); i++) {
			if (inorder[i] == rootval)dex = i;

		}
		for (int i = 0; i < inorder.size(); i++) {
			if (i < dex) left.push_back(inorder[i]);
			if (i > dex) right.push_back(inorder[i]);
		}
		preorder.erase(preorder.begin());
		root->left = __buildTree1(left,preorder);
		root->right = __buildTree1(right, preorder);
		return root;
	}
}

Tree::Tree(vector<int> inorder, vector<int> postorder,int flag) {
	treeroot = __buildTree2(inorder, postorder);
}

TreeNode*Tree::__buildTree2(vector<int> &inorder, vector<int> &postorder) {
	if (!inorder.size() || !postorder.size()) return NULL;
	else {
		int rootval = postorder[postorder.size() - 1];
		TreeNode *root = new TreeNode(rootval);
		int dex;
		vector<int> left, right;
		for (int i = 0; i < inorder.size(); i++) {
			if (inorder[i] == rootval)dex = i;

		}
		for (int i = 0; i < inorder.size(); i++) {
			if (i < dex) left.push_back(inorder[i]);
			if (i > dex) right.push_back(inorder[i]);
		}
		postorder.pop_back();
		root->right = __buildTree2(right, postorder);
		root->left = __buildTree2(left, postorder);
		return root;
	}
}
vector<int> Tree::preorder() {
	vector<int> res;
	if (!treeroot) return res;
	else {
		TreeNode *now = treeroot;

		stack<TreeNode*> sta;
		sta.push(now);
		while (sta.size()) {
			TreeNode *temp = sta.top();
			res.push_back(temp->val);
			sta.pop();
			if (temp->right) sta.push(temp->right);
			if (temp->left)  sta.push(temp->left);
		}return res;
	}
}

vector<int> Tree::inorder() {
	vector<int> record;
	if (!treeroot) return record;
	else {
		TreeNode *now = treeroot;
		stack<TreeNode*> sta;
		while (now) {
			sta.push(now);
			now = now->left;
		}
		while (sta.size()) {
			TreeNode *temp = sta.top();
			record.push_back(temp->val);
			sta.pop();
			temp = temp->right;
			while (temp) {
				sta.push(temp);
				temp = temp->left;
			}
		}
		return record;
	}
}



vector<int> Tree::postorder() {
	vector<int> res;
	if (!treeroot) return res;
	else {
		stack<TreeNode*> sta;
		TreeNode*now = treeroot;
		while (now) {
			sta.push(now);
			now = now->left;
		}
		sta.push(now);
		
		while (sta.size()) {
			TreeNode *temp = sta.top();
			sta.pop();
			
			if(temp)  res.push_back(temp->val);

			if (!sta.size() || temp == sta.top()->right) continue;
			
			TreeNode*now = sta.top()->right;
			while (now) {
				sta.push(now);
				now = now->left;
			}
			sta.push(now);
		}
		return res;
	}
}


//后序遍历顺序为：左右中。则把前序遍历反过来，先排出 中右左，再令数组反转，得到结果
vector<int> Tree::postorder2() {
	vector<int> res;
	if (!treeroot) return res;
	else {
		TreeNode *now = treeroot;

		stack<TreeNode*> sta;
		sta.push(now);
		while (sta.size()) {
			TreeNode *temp = sta.top();
			res.push_back(temp->val);
			sta.pop();
			if (temp->left) sta.push(temp->left);        //这里与前序遍历相反，先进左结点，再进右结点，达到 中右左 的效果
			if (temp->right)  sta.push(temp->right);
		}
		reverse(res.begin(),res.end());         //反转，变为 左右中，即为后续遍历的结果
		return res;
	}
}

vector<int> Tree::levelorder() {
	vector<int> res;
	if (!treeroot) return res;
	else {
		queue<TreeNode*> que;
		TreeNode*now = treeroot;
		que.push(now);
		while (que.size()) {
			TreeNode *temp = que.front();
			res.push_back(temp->val);
			que.pop();
			if (temp->left) que.push(temp->left);
			if (temp->right) que.push(temp->right);
		}
		return res;
	}
}
int Tree::size() {
	return __size(treeroot);
}
int Tree::__size(TreeNode*root) {
	if (!root) return 0;
	else if (!root->left && !root->right) return 1;
	else {
		int left = __size(root->left);
		int right = __size(root->right);
		return left + right + 1;
	}
}
