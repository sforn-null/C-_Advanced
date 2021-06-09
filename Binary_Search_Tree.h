//#pragma once
//#include<iostream>
//using namespace std;
//
////二叉搜索树
////树本身和所有子树的左节点都比根小，而右节点都比根大
//
////二叉搜索树实现
//template<class K>
//struct BSTreeNode
//{
//	BSTreeNode<K>* _left;
//	BSTreeNode<K>* _right;
//	K _key;
//
//	BSTreeNode(const K& key)
//		:_left(nullptr)
//		,_right(nullptr)
//		,_key(key)
//	{}
//};
//
//template<class K>
//class BSTree
//{
//	typedef BSTreeNode<K> Node;
//public:
//	bool Insert(const K& key)
//	{
//		//之所以有bool返回值，因为不能插入重复的数字
//		if (_root == nullptr)
//		{
//			_root = new Node(key);
//			return true;
//		}
//		Node* cur = _root;
//		Node* parent = nullptr;
//		while (cur)
//		{
//			parent = cur;
//			if (cur->_key > key)
//			{
//				cur = cur->_left;
//			}
//			else if (cur->_key < key)
//			{
//				cur = cur->_right;
//			}
//			else
//			{
//				return false;
//			}
//		}
//		cur = new Node(key);
//		if (parent->_key > key)
//		{
//			parent->_left = cur;
//		}
//		else
//		{
//			parent->_right = cur;
//		}
//
//		return true;
//	}
//
//	void _InOrder(Node* root)
//	{
//		if (root == nullptr)
//		{
//			return;
//		}
//		_InOrder(root->_left);
//		cout << root->_key << " ";
//		_InOrder(root->_right);
//	}
//	void InOrder()
//	{
//		_InOrder(_root);
//		cout << endl;
//	}
//
//	bool Find(const K& key)
//	{
//		Node* cur = _root;
//		while (cur)
//		{
//			if (cur ->_key < key)
//			{
//				cur = cur->_right;
//			}
//			else if (cur->_key > key)
//			{
//				cur = cur->_left;
//			}
//			else
//			{
//				return true;
//			}
//		}
//		return false;
//	}
//
//	bool Erase(const K& key)
//	{
//		Node* parent = nullptr;
//		Node* cur = _root;
//
//		while (cur)
//		{
//			if (cur->_key < key)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (cur->_key > key)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//				//找到了，开始删除
//				//分为三种情况
//				//左为空
//				//要根据cur是在父亲的左边还是右边
//				//来判断让父亲的左边还是右边指向cur的右边
//				if (cur->_left == nullptr)
//				{
//					if (cur == _root)
//					{
//						_root = cur->_right;
//					}
//					else
//					{
//						if (cur == parent->_right)
//						{
//							parent->_right = cur->_right;
//						}
//						else
//						{
//							parent->_left = cur->_right;
//						}
//					}
//					
//					delete cur;
//				}
//				else if (cur->_right == nullptr)
//				{
//					//右为空
//					if (cur == _root)
//					{
//						_root = cur->_left;
//					}
//					else
//					{
//						if (cur == parent->_right)
//						{
//							parent->_right = cur->_left;
//						}
//						else
//						{
//							parent->_left = cur->_left;
//						}
//					}
//					
//					delete cur;
//				}
//				else
//				{
//					//都不为空
//					Node* rightMinParent = cur;
//					Node* rightMin = cur->_right;
//					while (rightMin->_left)
//					{
//						rightMinParent = rightMin;
//						rightMin = rightMin->_left;
//					}
//					//替代删除节点
//					cur->_key = rightMin->_key;
//					//转换成删除rightMin
//					if(rightMin == rightMinParent->_left)
//						rightMinParent->_left = rightMin->_right;
//					else
//						rightMinParent->_right = rightMin->_right;
//					delete rightMin;
//				}
//				return true;
//			}
//		}
//		return false;
//	}
//
//private:
//	Node* _root = nullptr;
//};
//
//
//void Test_BSTree1()
//{
//	BSTree<int> t;
//	int a[] = { 5,3,4,1,7,8,2,6,0,9 };
//	for (auto e : a)
//	{
//		t.Insert(e);
//	}
//	t.InOrder();
//
//
//	t.Erase(5);
//	t.InOrder();
//
//	t.Erase(8);
//	t.InOrder();
//
//	t.Erase(1);
//	t.InOrder();
//
//	t.Erase(5);
//	t.InOrder();
//
//	for (auto e : a)
//	{
//		t.Erase(e);
//		t.InOrder();
//	}
//}
