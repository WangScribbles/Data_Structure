//key-value型二叉搜索树

#pragma once
#include <iostream>
#include <string>
using namespace std;

template<class K, class V>
struct BSTreeNode
{
	BSTreeNode(const K& key, const V& value)
		:_left(nullptr)
		, _right(nullptr)
		, _key(key)
		,_value(value)
	{}

	BSTreeNode<K, V>* _left;
	BSTreeNode<K, V>* _right;
	K _key;
	V _value;
};

template<class K, class V>
class BSTree
{
	typedef BSTreeNode<K, V> Node;
public:
	//插入
	bool Insert(const K& key, const V& value);
	//查找
	Node* Find(const K& key);
	//删除
	bool Erase(const K& key);
	//遍历
	void _InOrder(Node* root);
	void InOrder();

private:
	Node* _root = nullptr;
};

//插入
template<class K, class V>
bool BSTree<K, V>::Insert(const K& key, const V& value)
{
	if (_root == nullptr)
	{
		_root = new Node(key, value);
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

	cur = new Node(key, value);
	if (parent->_key < cur->_key)
	{
		parent->_right = cur;
	}
	else
	{
		parent->_left = cur;
	}

	return true;
}

//查找
template<class K, class V>
typename BSTree<K, V>::Node* BSTree<K, V>::Find(const K& key)
{
	Node* cur = _root;
	while (cur)
	{
		if (cur->_key < key)
			cur = cur->_right;
		else if (cur->_key > key)
			cur = cur->_left;
		else
			return cur;
	}

	return nullptr;
}

//删除
template<class K, class V>
bool BSTree<K, V>::Erase(const K& key)
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
				cur->_value = rightMin->_value;

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
template<class K, class V>
void BSTree<K, V>::_InOrder(Node* root)
{
	if (root == nullptr)
		return;

	_InOrder(root->_left);
	cout << root->_key << ":" << root->_value << endl;
	_InOrder(root->_right);
}
template<class K, class V>
void BSTree<K, V>::InOrder()
{
	_InOrder(_root);
	cout << endl;
}

//测试
void TestKVBSTree01()
{
	BSTree<string, string> dict;
	dict.Insert("apple", "苹果");
	dict.Insert("banana", "香蕉");
	dict.Insert("watermelon", "西瓜");

	string str;
	while (cin >> str)
	{
		BSTreeNode<string, string>* ret = dict.Find(str);
		if (ret)
		{
			cout << ret->_value << endl;
		}
		else
		{
			cout << "无此单词" << endl;
		}
	}
}

void TestKVBSTree02()
{
	string strArr[] = { "西瓜", "西瓜", "西瓜", "苹果", "苹果", "香蕉" };
	BSTree<string, int> countTree;

	for (auto str : strArr)
	{
		BSTreeNode<string, int>* ret = countTree.Find(str);
		if (ret == nullptr)
		{
			countTree.Insert(str, 1);
		}
		else
		{
			ret->_value++;
		}
	}

	countTree.InOrder();
}
