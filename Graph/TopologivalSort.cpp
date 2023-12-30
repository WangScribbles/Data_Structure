#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

template<class W>
struct Edge
{
    Edge(const W& w, int dsti)
        :_w(w)
        , _dsti(dsti)
        , _next(nullptr)
    {}

    W _w;
    Edge<W>* _next;
    int _dsti;
};

template<class V, class W>
class Graph
{
    typedef Edge<W> Edge;
public:
    Graph(const V* a, int n)
    {
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

    void AddEdge(const V& src, const V& dst, const W& w)
    {
        size_t srci = GetVertexIndex(src);
        size_t dsti = GetVertexIndex(dst);

		Edge* edge = new Edge(w, dsti);
		edge->_next = _tables[srci];
		_tables[srci] = edge;
    }

    vector<V> TopologicalSort()
    {
        vector<int> inDegree(_vertexs.size(), 0);
        for (size_t i = 0; i < _tables.size(); ++i)
        {
            Edge* edge = _tables[i];
            while (edge)
            {
                inDegree[edge->_dsti]++;
                edge = edge->_next;
            }
        }

        queue<int> q;
        for (size_t i = 0; i < inDegree.size(); ++i)
        {
            if (inDegree[i] == 0)
            {
                q.push(i);
            }
        }

        vector<V> result;
        while (!q.empty())
        {
            int index = q.front();
            q.pop();
            result.push_back(_vertexs[index]);

            Edge* edge = _tables[index];
            while (edge)
            {
                inDegree[edge->_dsti]--;
                if (inDegree[edge->_dsti] == 0)
                {
                    q.push(edge->_dsti);
                }
                edge = edge->_next;
            }
        }

        return result;
    }

private:
    vector<V> _vertexs;  // 顶点集合
    map<V, int> _indexMap;  // 顶点映射下标
    vector<Edge*> _tables;  // 邻接表
};

void test()
{
	string a[] = { "A", "B", "C", "D", "E" };
    Graph<string, int> g(a, 5);
    g.AddEdge("A", "B", 1);
    g.AddEdge("A", "C", 1);
    g.AddEdge("B", "D", 1);
    g.AddEdge("C", "D", 1);
    g.AddEdge("D", "E", 1);

    vector<string> result = g.TopologicalSort();
    for (const auto& vertex : result)
    {
        cout << vertex << " ";
    }
    cout << endl;
}

int main()
{
    test();

    return 0;
}