#include <iostream>
#include <stack>
using namespace std;

template<class T>
struct BTNode
{
	BTNode(const T& data)
		: _data(data)
		, _left(nullptr)
		, _right(nullptr)
	{}

	T _data;
	BTNode* _left;
	BTNode* _right;
};

template<class T>
class BinTree
{
	typedef BTNode<T> Node;
public:
	void _PrevOrderNonR(Node* _root)
	{
		if (_root == nullptr)
			return;

		stack<Node*> st;
		Node* cur = _root;
		while (cur != nullptr || !st.empty())
		{
			while (cur != nullptr)
			{
				cout << cur->_data << " ";
				st.push(cur);
				cur = cur->_left;
			}
			cur = st.top();
			st.pop();
			cur = cur->_right;
		}
	}

	void _InOrderNonR(Node* _root)
	{
		if (_root == nullptr) 
			return;

		stack<Node*> st;
		Node* cur = _root;
		while (cur != nullptr || !st.empty()) 
		{
			while (cur != nullptr) 
			{
				st.push(cur);
				cur = cur->_left;
			}
			cur = st.top();
			st.pop();
			cout << cur->_data << " ";
			cur = cur->_right;
		}
	}

	void _PostOrderNonR(Node* _root)
	{
		if (_root == nullptr) 
			return;

		stack<Node*> st;
		Node* cur = _root;
		Node* lastVisited = nullptr;
		while (cur != nullptr || !st.empty()) 
		{
			while (cur != nullptr) 
			{
				st.push(cur);
				cur = cur->_left;
			}
			cur = st.top();
			if (cur->_right == nullptr || cur->_right == lastVisited) 
			{
				cout << cur->_data << " ";
				st.pop();
				lastVisited = cur;
				cur = nullptr;
			}
			else 
			{
				cur = cur->_right;
			}
		}
	}

	void PrevOrderNonR()
	{
		_PrevOrderNonR(_root);
		cout << endl;
	}

	void InOrderNonR()
	{
		_InOrderNonR(_root);
		cout << endl;
	}

	void PostOrderNonR()
	{
		_PostOrderNonR(_root);
		cout << endl;
	}
private:
	Node* _root = nullptr;
};