#pragma once
#include <vector>
#include <map>
#include <string>

namespace link_table
{

template<class W>
struct Edge
{
	Edge(int dsti, const W& w)
		: _dsti(dsti)
		, _w(w)
		, _next(nullptr)
	{}
	
	//int _srci;
	int _dsti;
	W _w;
	Edge<W>* _next;
};

template<class V, class W, bool Direction = false>
class Graph
{
	typedef Edge<W> Edge;
public:
	// 图的创建

	Graph(const V* a, size_t n) // 传的是V类型的数组
	{
		_vertexs.resever(n);
		for (size_t i = 0; i < n; ++i)
		{
			_vertexs.push_back(a[i]);
			_indexMap[a[i]] = i;
		}
		
		_tables.resize(n, nullptr);
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

		Edge* eg = new Edge(dsti, w);
		eg->_next = _tables[srci];
		_tables[srci] = eg;
		
		// 无向图
		if (Direction == false)
		{
			Edge* eg = new Edge(srci, w);
			eg->_next = _tables[dsti];
			_tables[dsti] = eg;
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
		
		for (size_t i = 0; i < _tables.size(); ++i)
		{
			cout << _vertexs[i] << "[" << i << "]->";
			Edge* cur = _tables[i];
			while (cur)
			{
			cout << "[" << _vertexs[cur->_dsti] << ":" << cur->_dsti << ":" << cur->_w << "]->"; 
				cur = cur->_next;
			}
			cout << "nullptr" << endl;
		}
	}
	
private:
	vector<V>   _vertexs;   // 顶点集合
	map<V, int> _indexMap;  // 顶点映射下标 
	vector<Edge*> _tables;   // 邻接表
};	

void TestGraph()
{
	string a[] = { "张三", "李四", "王五", "赵六" };
	Graph<string, int> g(a, 4);
	g.AddEage("张三", "李四", 100);
	g.AddEage("张三", "王五", 200);
	g.AddEage("王五", "赵六", 30);
	
	g.print();
}

}  // end of namespace link_table