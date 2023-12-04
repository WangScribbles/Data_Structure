#pragma once
#include <iostream>
#include <assert.h>
#include <time.h>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	pair<K, V> _kv;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	int _bf;  // balance factor

	AVLTreeNode(const pair<K, V>& kv)
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{}
};

template<class K, class V>
struct AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
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

		// 1、更新平衡因子
		while (parent) // parent为空，也就更新到根
		{
			// 新增在右，parent->bf++;
			// 新增在左，parent->bf--;
			if (cur == parent->_left)
			{
				parent->_bf--;
			}
			else
			{
				parent->_bf++;
			}

			// 是否继续更新依据：子树的高度是否变化
			// 1、parent->_bf == 0说明之前parent->_bf是 1 或者 -1
			// 说明之前parent一边高一边低，这次插入填上矮的那边，parent所在子树高度不变，不需要继续往上更新
			// 2、parent->_bf == 1 或 -1 说明之前是parent->_bf == 0，两边一样高，现在插入一边更高了，
			// parent所在子树高度变了，继续往上更新
			// 3、parent->_bf == 2 或 -2，说明之前parent->_bf == 1 或者 -1，现在插入严重不平衡，违反规则
			// 就地处理--旋转

			// 旋转：
			// 1、让这颗子树左右高度不超过1
			// 2、旋转过程中继续保持他是搜索树
			// 3、更新调整孩子节点的平衡因子
			// 4、让这颗子树的高度跟插入前保持一致
			if (parent->_bf == 0)
			{
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				// 说明parent所在子树的高度变了，继续往上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				// parent所在的子树出现不平衡了，需要旋转处理
				// 1、旋转前提是保持它依旧是搜索二叉树
				// 2、旋转成平衡树
				if (parent->_bf == 2)
				{
					if (cur->_bf == 1)
					{
						RotateL(parent);
					}
					else if (cur->_bf == -1)
					{
						RotateRL(parent);
					}
				}
				else if (parent->_bf == -2)
				{
					if (cur->_bf == -1)
					{
						RotateR(parent);
					}
					else if (cur->_bf == 1)
					{
						RotateLR(parent);
					}
				}
				else
				{
					assert(false);
				}
				
				// 旋转完成后，parent所在的树的高度恢复到了插入节点前的高度
				//如果是子树，对上层没有影响，更新结束
				break;
			}
			else
			{
				assert(false);
			}
		}

		return true;
	}
	
	//左单旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		// 1、原来parent是这棵树的根，现在subR是根
		// 2、parent为根的树只是整颗树中的子树，改变链接关系时，subR要顶替他的位置
		if (ppNode == nullptr) // 或者 if (_root == parent)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}

		parent->_bf = subR->_bf = 0;
	}
	
	//右单旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		//if (_root == parent)
		if (ppNode == nullptr)
		{
			_root = subL;
			_root->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;

			subL->_parent = ppNode;
		}

		subL->_bf = parent->_bf = 0;
	}

	// 左右双旋
	//先左单旋，后右单旋
	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		//先左单旋，后右单旋
		RotateL(parent->_left);
		RotateR(parent);

		if (bf == -1) // subLR左子树新增
		{
			subL->_bf = 0;
			parent->_bf = 1;
			subLR->_bf = 0;
		}
		else if (bf == 1) // subLR右子树新增
		{
			parent->_bf = 0;
			subL->_bf = -1;
			subLR->_bf = 0;
		}
		else if (bf == 0) // subLR自己就是新增
		{
			parent->_bf = 0;
			subL->_bf = 0;
			subLR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	// 右左双旋
	// 先右单旋，后左单旋
	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		// 先右单旋，后左单旋
		RotateL(parent->_right);
		RotateR(parent);

		if (bf == -1) // subLR左子树新增
		{
			parent->_bf = 0;
			subR->_bf = 1;
			subRL->_bf = 0;
		}
		else if (bf == 1) // subLR右子树新增
		{
			parent->_bf = -1;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else if (bf == 0) // subLR自己就是新增
		{
			parent->_bf = 0;
			subR->_bf = 0;
			subRL->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

	void _Inorder(Node* root)
	{
		if (root == nullptr)
			return;

		_Inorder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_Inorder(root->_right);
	}

	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		
		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);
		
		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}

	bool _IsBalance(Node* root)
	{
		if (root == nullptr)
			return true;

		int leftHeight = Height(root->_left);
		int rightHeight = Height(root->_right);

		if (rightHeight - leftHeight != root->_bf)
		{
			cout <<root->_kv.first<<"平衡因子异常" << endl;
			return false;
		}

		return abs(rightHeight - leftHeight) < 2
			&& _IsBalance(root->_left)
			&& _IsBalance(root->_right);
	}
	
	bool IsBalance()
	{
		return _IsBalance(_root);
	}

private:
	Node* _root = nullptr;
};

void TestAVLTree01()
{
	//int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int, int> t;
	for (auto e : a)
	{
		t.Insert(make_pair(e, e));
	}

	t.Inorder();

	cout << t.IsBalance() << endl;
}

void TestAVLTree02()
{
	srand(time(0));
	const size_t N = 10000;
	AVLTree<int, int> t;
	for (size_t i = 0; i < N; ++i)
	{
		size_t x = rand();
		t.Insert(make_pair(x, x));
		//cout << t.IsBalance() << endl;
	}

	//t.Inorder();

	cout << t.IsBalance() << endl;
}