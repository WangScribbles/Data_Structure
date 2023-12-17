#pragma once
#include <vector>
#include <map>
#include <queue>

namespace matrix
{

template<class V, class W, W MAX_W = INT_MAX, bool Direction = false>
class Graph
{
public:
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

		_matrix[srci][dsti] = w;
		
		// 无向图
		if (Direction == false)
		{
			_matrix[dsti][srci] = w;
		}
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

}  // end of namespace matrix