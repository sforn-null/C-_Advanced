#pragma once
#include<iostream>
#include<map>
using namespace std;

enum Colour
{
	BLACK,
	RED,
};

template<class K,class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	pair<K, V> _kv;

	Colour _col;


	RBTreeNode(const pair<K, V>& kv)
		: _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _col(RED)
	{}
};

template<class K,class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		// 1.按搜索树的规则进行插入
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}

		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}
		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		//这里我们选择给新插入的为红色的
		//因为我们比较好控制插入的不能连续为红色这点
		//而选择黑色，我们要面对的问题是任意结点到叶子结点所经过的结点黑色个数相同
		//而这点我们不好控制
		cur->_col = RED;
		while (parent && parent->_col == RED)
		{
			//红黑色的条件关键看叔叔
			Node* grandfther = parent->_parent;
			if (grandfther->_left == parent)
			{
				Node* uncle = grandfther->_right;
				//情况1，如果uncle存在并且为红
				//那么将父亲的颜色和uncle的颜色变为黑
				//并且把grandfather变红
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfther->_col = RED;

					//继续往上处理
					cur = grandfther;
					parent = cur->_parent;
				}
				else//情况2或3，叔叔不存在或者叔叔为黑
				{
					//父亲在祖父左边而cur在父亲的右边，说明要双旋
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}
					RotateR(grandfther);
					grandfther->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
			else
			{
				Node* uncle = grandfther->_left;
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfther->_col = RED;

					cur = grandfther;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}
					RotateL(grandfther);
					grandfther->_col = RED;
					parent->_col = BLACK;
					break;
				}
			}
		}
		_root->_col = BLACK;
		return true;
	}

	//左单旋
	void RotateL(Node* parent)
	{
		//Node* subR = parent->_right;
		//parent->_right = subR->_left;
		//subR->_left = parent;
		//二叉链这样写没问题，
		//但是这里是三叉链，还有个parent

		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		//1. 原理parent是这个树的根，现在subR是这个树的根
		//2. parent为根的树只是整棵树中的子树，如果改变链接关系，
		//那么subR要顶替之前parent的位置
		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}
			subR->_parent = ppNode;
		}
	}

	//右单旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;


		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}
			subL->_parent = ppNode;
		}
	}

	//右左双旋
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		
	}

	//左右双旋
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subL->_bf;

		RotateL(subL);
		RotateR(parent);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}
		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
	void InOrder()
	{
		_InOrder(_root);
	}

private:
	Node* _root = nullptr;
};


void TestRBTree()
{
	int a[] = { 16,3,7,11,9,26,18,14,15 };
	RBTree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}

	t.InOrder();

}