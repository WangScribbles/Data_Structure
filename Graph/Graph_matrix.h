#pragma once
#include <vector>
#include <map>
#include <queue>
#include <functional>

namespace matrix
{

template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
class Graph
{
	typedef Graph<V, W, MAX_W, Direction> Self;
public:
	Graph() = default;

	// 图的创建
	// 1.IO输入  -- 不方便测试，oj中更适合
	// 2.图结构关系写到文件，读取文件
	// 3.手动添加边
	Graph(const V* a, size_t n) // 传的是V类型的数组
	{
		_vertexs.resever(n);
		for (size_t i = 0; i < n; ++i)
		{
			_vertexs.push_back(a[i]);
			_indexMap[a[i]] = i;
		}
		
		_matrix.resize(n);
		for (size_t i = 0; i < _matrix.size(); ++i)
		{
			_matrix[i].resize(n, MAX_W);
		}
	}
	
	size_t GetVertexIndex(const V& v)
	{
		auto it = _indexMap.find(v);
		if (it != _indexMap.end())
		{
			return it->second;
		}
		else
		{
			throw invalid_argument("顶点不存在");
			
			return -1;
		}
	}
	
	// 也可以多一个添加顶点的函数
	void AddEage(const V& src, const V& dst, const W& w)
	{
		size_t srci = GetVertexIndex(src);
		size_t dsti = GetVertexIndex(dst);

		/*
		_matrix[srci][dsti] = w;
		
		// 无向图
		if (Direction == false)
		{
			_matrix[dsti][srci] = w;
		}
		*/
		
		_AddEage(srci, dsti, w);
	}
	
	void Print()
	{
		// 顶点
		cout << "  ";
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{
			cout << "[" << i << "]" << "->" << _vertexs[i] << endl;
		}
		cout << endl;
		
		// 矩阵
		for (size_t i = 0; i < _vertexs.size(); ++i)
		{ 
			//cout << i << " ";  // 横下标
			printf("%4d", i);
		}
		
		for (size_t i = 0; i < _matrix.size(); ++i)
		{
			cout << i << " ";  // 竖下标
			for (size_t j = 0; j < _matrix[i].size(); ++j)
			{
				if (_matrix[i][j] == MAX_W)
					//cout << "* ";
					printf("%4c", '*');
				else
					//cout << _matrix[i][j] << " ";
					printf("%4d", _matrix[i][j]);
			}
			cout << endl;
		}
		cout << endl;
	}
	
	void BFS(const V& src)
	{
		size_t srci = GetVertexIndex();
	
		// 队列和标记数组
		queue<int> q;
		vector<bool> visited(_vertexs.size(), false);
		
		q.push(srci);
		visited[srci] = true;
		int levelSize = 1;
		
		size_t n = _vertexs.size();
		while (!q.empty())
		{
			// 一层一层出
			for (int i  = 0; i < levelSize; ++i)
			{
				int front = q.front();
				q.pop();
				cout << front << ":" << _vertexs[front] << " ";
				
				// 把顶点front的邻接顶点入队
				for (size_t i = 0; i < n; ++i)
				{
					if (_matrix[front][i] != MAX_W)
					{
						if (visited[i] == false)
						{
							q.push(i);
							visited[i] = true;
						}
					}
				}
			}
			cout << endl;
			
			levelSize = q.size();
		}
		
		cout << endl;
	}
	
	void _DFS(size_t srci, vector<bool>& visited)
	{
		cout << srci << ":" << _vertexs[srci] << endl;
		visited[srci] = true;
		
		// 找一个srci相邻的没有访问过的点，去往深度遍历
		for (size_t i  =0; i < _vertexs.size(); ++i)
		{
			if (_matrix[srci][i] != MAX_W && visited[i] == false)
			{
				_DFS(i, visited);
			}
		}
	}
	
	void DFS(const V& src)
	{
		size_t srci = GetVertexIndex(src);
		vector<bool> visited(_vertexs.size(), false);
		
		_DFS(srci, visited);
		
		// 不是连通图
		// 遍历visited数组，然后DFS
	}

	struct Edge
	{
		Edge(size_t srci, size_t dsti, const W& w)
			:_srci(srci)
			, _dsti(dsti)
			, _w(w)
		{}
		
		bool operator>(const Edge& e) const
		{
			return _w > e._w;
		}
		
		size_t _srci;
		size_t _dsti;
		W _w;
	};
	
	void _AddEage(size_t src, size_t dst, const W& w)
	{
		_matrix[srci][dsti] = w;
		
		// 无向图
		if (Direction == false)
		{
			_matrix[dsti][srci] = w;
		}
	}

	W Kurskal(Self& minTree)
	{
		size_t n = _vertexs.size();
		
		minTree._vertexs = _vertexs;
		minTree._indexMap = _indexMap;
		minTree._matrix.resize(n);
		for (size_t i = 0; i < n; ++i)
		{
			minTree._matrix[i].resize(n, MAX_W);
		}
		
		priority_queue<Edge, vector<Edge>, greater<Edge>> minque;
		
		for (size_t i = 0; i < n; ++i)
		{
			for (size_t j = 0; j < n; ++j)
			{
				if (i < j && _matrix[i][j] != MAX_W)
				{
					minque.push(Edge(i, j, _matrix[i][j]));
				}
			}
		}
		
		// 选出(n - 1)条边
		int size = 0;
		W totalW = W();
		UinonFindSet ufs(n);
		while (!minque.empty())
		{
			Edge min = minque.top();
			minque.pop();
			
			if (!ufs.InSet(min._srci, min._dsti))
			{
				cout << _vertexs[min._srci] << "->" << _vertexs[min._dsti] << ":" << min._w << endl;
				minTree._AddEage(mid._srci, min._dsti, min._w);
				ufs.Union(min._srci, min._dsti);
				++size;
				totalW += min._w;
			}
			else
			{
				cout << "构成环了：";
				cout << _vertexs[min._srci] << "->" << _vertexs[min._dsti] << ":" << min._w << endl;
			}
		}
		
		if (size == n - 1)
		{
			return totalW;
		}
		else
		{
			return W();
		}
	}

private:
	vector<V>   _vertexs;       // 顶点集合
	map<V, int> _indexMap;      // 顶点映射下标 
	vector<vector<W>> _matrix;  // 邻接矩阵
};	

void TestGraph()
{
	Graph<char, int, INT_MAX, true> g("0123", 4);
	g.AddEage('0', '1', 1);
	g.AddEage('0', '3', 4);
	g.AddEage('1', '3', 2);
	g.AddEage('1', '2', 9);
	g.AddEage('2', '3', 8);
	g.AddEage('2', '1', 5);
	g.AddEage('2', '0', 3);
	g.AddEage('3', '2', 6);
	
	g.Print();
}

 void TestBDFS()
 {
	string a[] = { "张三", "李四", "王五", "赵六", "周七" };
	Graph<string, int> g(a, sizeof(a) / sizeof(string));
	g.AddEage("张三", "李四", 100);
	g.AddEage("张三", "王五", 200);
	g.AddEage("王五", "赵六", 30);
	g.AddEage("王五", "周七", 30);
	g.Print();
	
	g.BFS("张三");
	//g.DFS("张三");
 }

void TestGraphMinTree()
{
     const char* str = "abcdefghi";
     Graph<char, int> g(str, strlen(str));
     g.AddEdge('a', 'b', 4);
     g.AddEdge('a', 'h', 8);
     //g.AddEdge('a', 'h', 9);
     g.AddEdge('b', 'c', 8);
     g.AddEdge('b', 'h', 11);
     g.AddEdge('c', 'i', 2);
     g.AddEdge('c', 'f', 4);
     g.AddEdge('c', 'd', 7);
     g.AddEdge('d', 'f', 14);
     g.AddEdge('d', 'e', 9);
     g.AddEdge('e', 'f', 10);
     g.AddEdge('f', 'g', 2);
     g.AddEdge('g', 'h', 1);
     g.AddEdge('g', 'i', 6);
     g.AddEdge('h', 'i', 7);
	 
     Graph<char, int> kminTree;
     cout << "Kruskal:" << g.Kruskal(kminTree) << endl;
     kminTree.Print();
	 
     Graph<char, int> pminTree;
     cout << "Prim:" << g.Prim(pminTree, 'a') << endl;
     pminTree.Print();
}

}  // end of namespace matrix
