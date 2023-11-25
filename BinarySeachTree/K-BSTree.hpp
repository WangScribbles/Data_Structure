//key型二叉搜索树

#pragma once
#include <iostream>
using namespace std;

template<class K>
struct BSTreeNode
{
	BSTreeNode(const K& key)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
	{}

	BSTreeNode<K>* _left;
	BSTreeNode<K>* _right;
	K _key;
};

template<class K>
class BSTree
{
	typedef BSTreeNode<K> Node;
public:
	//插入
	bool Insert(const K& key);
	//查找
	bool Find(const K& key);
	//删除
	bool Erase(const K& key);
	//遍历
	void _InOrder(Node* root);
	void InOrder();
	
private:
	Node* _root = nullptr;
};

//插入
template<class K>
bool BSTree<K>::Insert(const K& key)
{
	if (_root == nullptr)
	{
		_root = new Node(key);
		return true;
	}

	Node* parent = nullptr;
	Node* cur = _root;
	while (cur)
	{
		if (cur->_key < key)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_key > key)
		{
			parent = cur;
			cur = cur->_left;
		}
		else
		{
			return false;
		}
	}

	cur = new Node(key);
	if (parent->_key < cur->_key)
		parent->_right = cur;
	else
		parent->_left = cur;

	return true;
}

//查找
template<class K>
bool BSTree<K>::Find(const K& key)
{
	Node* cur = _root;
	while (cur)
	{
		if (cur->_key < key)
			cur = cur->_right;
		else if (cur->_key > key)
			cur = cur->_left;
		else
			return true;
	}

	return false;
}

//删除
template<class K>
bool BSTree<K>::Erase(const K& key)
{
	Node* parent = nullptr;
	Node* cur = _root;
	while (cur)
	{
		if (cur->_key < key)
		{
			parent = cur;
			cur = cur->_right;
		}
		else if (cur->_key > key)
		{
			parent = cur;
			cur = cur->_left;
		}
		else
		{
			//找到了，开始删除
			//1、左为空
			//2、右为空
			//3、左右都不为空
			if (cur->_left == nullptr)
			{
				if (cur == _root)
				{
					_root = cur->_right;
				}
				else
				{
					if (parent->_left == cur)
						parent->_left = cur->_right;
					else
						parent->_right = cur->_right;
				}

				delete cur;
			}
			else if (cur->_right == nullptr)
			{
				if (cur == _root)
				{
					_root = cur->_left;
				}
				else
				{
					if (parent->_left == cur)
						parent->_left = cur->_left;
					else
						parent->_right = cur->_left;
				}

				delete cur;
			}
			else //找右树最小节点
			{
				Node* rightMinParent = cur;
				Node* rightMin = cur->_right;
				while (rightMin->_left)
				{
					rightMinParent = rightMin;
					rightMin = rightMin->_left;
				}

				//替代删除法
				cur->_key = rightMin->_key;

				//转换成删除rightMin(rightMin是左为空，让父亲指向他的右)
				if (rightMin == rightMinParent->_left)
					rightMinParent->_left = rightMin->_right;
				else
					rightMinParent->_right = rightMin->_right;

				delete rightMin;
			}

			return true;
		}
	}

	return false;
}

//遍历
template<class K>
void BSTree<K>::_InOrder(Node* root)
{
	if (root == nullptr)
		return;

	_InOrder(root->_left);
	cout << root->_key << " ";
	_InOrder(root->_right);
}
template<class K>
void BSTree<K>::InOrder()
{
	_InOrder(_root);
	cout << endl;
}

//测试
void TestKBSTree()
{
	BSTree<int> t;
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };

	for (auto e : a)
	{
		t.Insert(e);
	}

	t.InOrder();

	t.Erase(7);
	t.InOrder();
}
