#pragma once
#include <vector>
#include <map>

#if 0

template<class T>
class UnionFindSet
{
public:
	UnionFindSet(const T* a, size_t n)
	{
		_a.reserve(n);
		for (size_t i = 0; i < _a.size(); ++i)
		{
			_a.push_back(a[i]);
			_indexMap[a[i]] = i;
		}
	}
	
private:
	vector<T> _a;  			// 编号找人
	map<T, int> _indexMap;  // 人找编号
};

#endif


class UnionFindSet
{
public:
	UnionFindSet(size_t n)
		: _ufs(n, -1)
	{}
	
	int FindRoot(int x)  // 可压缩路径
	{
		int parent = x;
		while (_ufs[parent] >= 0)
		{
			parent = _ufs[parent];
		}
		
		return parent;
	}
	
	void Union(int x1, int x2)
	{
		int root1 = FindRoot(x1);
		int root2 = FindRoot(x2);
		
		// 如果本身在一个集合，就没必要合并
		if (root1 == root2)
			return;
		
		// 如果想大的合并到小的去
		if (root1 > root2)
			swap(root1, root2);
		
		_ufs[root1] += _ufs[root2];
		_ufs[root2] = root1;
	}
	
	// 是否在同一个集合
	bool InSet(int x1, int x2)
	{
		return FindRoot(x1) == FindRoot(x2);
	}
	
	// 有几个集合
	size_t SetSize()
	{
		size_t size = 0;
		
		for (auto& e : _ufs)
		{
			if (e < 0)
				++size;
		}
		
		return size;
	}
private:
	vector<int> _ufs;
}