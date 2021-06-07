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
		// 1.���������Ĺ�����в���
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
		//��������ѡ����²����Ϊ��ɫ��
		//��Ϊ���ǱȽϺÿ��Ʋ���Ĳ�������Ϊ��ɫ���
		//��ѡ���ɫ������Ҫ��Ե������������㵽Ҷ�ӽ���������Ľ���ɫ������ͬ
		//��������ǲ��ÿ���
		cur->_col = RED;
		while (parent && parent->_col == RED)
		{
			//���ɫ�������ؼ�������
			Node* grandfther = parent->_parent;
			if (grandfther->_left == parent)
			{
				Node* uncle = grandfther->_right;
				//���1�����uncle���ڲ���Ϊ��
				//��ô�����׵���ɫ��uncle����ɫ��Ϊ��
				//���Ұ�grandfather���
				if (uncle && uncle->_col == RED)
				{
					parent->_col = BLACK;
					uncle->_col = BLACK;
					grandfther->_col = RED;

					//�������ϴ���
					cur = grandfther;
					parent = cur->_parent;
				}
				else//���2��3�����岻���ڻ�������Ϊ��
				{
					//�������游��߶�cur�ڸ��׵��ұߣ�˵��Ҫ˫��
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

	//����
	void RotateL(Node* parent)
	{
		//Node* subR = parent->_right;
		//parent->_right = subR->_left;
		//subR->_left = parent;
		//����������дû���⣬
		//���������������������и�parent

		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		//1. ԭ��parent��������ĸ�������subR��������ĸ�
		//2. parentΪ������ֻ���������е�����������ı����ӹ�ϵ��
		//��ôsubRҪ����֮ǰparent��λ��
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

	//�ҵ���
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

	//����˫��
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;
		RotateR(parent->_right);
		RotateL(parent);
		
	}

	//����˫��
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