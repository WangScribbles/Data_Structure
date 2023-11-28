#pragme once
#include <string>

namespace ws
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		
		vector()
			:_start(nullptr)
			, finish(nullptr)
			, _endofstorage(nullptr);
		{}
		
		//深拷贝
		//法一
		vector(const vector<T>& v)
		{
			_start = new T[v.capacity()];
			_finish = _start;
			_endofstorage = _start + v.capacity();
			
			for (size_t i = ; i < v.size(); ++i)
			{
				*_fin = v[i];
				++_finish;
			}
		}
		//法二
		vector(const vector<T>& V)
			:_start(nullptr)
			, _finish(nullptr)
			, _endofstorage(nullptr)
		{
			reserve(v.capacity());
			for (const auto& e : v)
			{
				push_back(e);
			}
		}
		
		vector<T>& operator=(const vector<T>& v)
		{
			if (this != &v)
			{
				delete[] _start;
				_start = new T[v.capacity()];
				memcpy(_start, v._start, sizeof(T)* v.size());
			}
			
			return *this;
		}
		//现代写法
		{
			vector<T>& operator=(vector<T> v)
			{
				/*
				swap(_start, v._start);（调全局的）
				swap(_finish, v._finish);
				swap(_endofstorage, v._endofstorage);
				*/
				
				//调用自己写的(this指针)
				swap(v);
				
				return *this;
			}
		}
		
		//用algorithm中的swap(v1, v2)内部是深拷贝，代价大
		void swap(vector<T>& v)
		{
			::swap(_start, v._start);  //不加全局域会调用自己写的swap()，参数匹配不上报错
			::swap(_finish, v._finish);
			::swap(_endofstorage, v._endofstorage);
		}
		
		
		~vector()
		{
			delete[] _start;
			_start = _finish = _endofstorage = nullptr;
		}
		
		iterator begin()
		{
			return _start;
		}
		
		iterator end()
		{
			return _finish;
		}
		
		const_iterator begin() const
		{
			return _start;
		}
		
		const_iterator end() const
		{
			return _finish;
		}
		
		size_t size() const
		{
			return _finish - _start;
		}
		
		size_t capacity() const
		{
			return _endofstorage - _start;
		}
		
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)  //开始时容量为0，_start是空指针
				{
					//按字节拷贝，浅拷贝
					//memcpy(tmp, _start, sizeof(T) * sz); //参数不能为空指针
					
					//test()解决方法
					for (size_t i = 0; i < sz; i++)
					{
						tmp[i] = _start[i]; //调用T的operator= 深拷贝
					}
					delete[] _start;
					
					delete[] _start;
				}
				_start = tmp;
				_finish = tmp + sz;
				_endofstorage = tmp + n;
			}
		}
		
		//val是一个对象
		//匿名对象初始化编译器优化，不会调用拷贝构造，直接将匿名对象转化为该对象
		void resize(size_t n, const T& val = T())  //const引用可以延长匿名对象的生命周期，以确保在引用作用域内仍可以使用匿名对象
		{
			if (n < size())
			{
				_finish = _start + n;
			}
			else
			{
				if (n > capacity())
				{
					reserve(n);
				}
				
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
		}
		
		void push_back(const T& x)
		{
			if (_finish == _endofstorage)
			{
				size_t newCapacity = capacity() == 0 ? 2 : capacity() * 2;
				resever(newCapacity);
			}
			
			*_finish = x;
			++_finish;
		}
		
		void pop_back(const T& x)
		{
			assert(_start < _finish);
			
			--_finish;
		}
		
		void insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);
			
			if (_finish == _endofstorage)
			{
				size_t n = pos - _start;  //解决方法
				size_t newCapacity = capacity() == 0 ? 2 : capacity() * 2;
				resever(newCapacity);
				
				pos = _start + n;  //解决方法
			}
			
			iterator end = _finish - 1; //end指向最后一个元素
			
			//若扩容，pos指向旧空间，存在迭代器失效。
			while (end >= pos)  //pos == finish时，>=不进去。尾插
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
		}
		
		iterator erase(iterator pos)
		{
			assert(pos <= _finish);
			
			iterator it = pos;
			while (it < _finish)
			{
				*it = *(it + 1);
				++it;
			}
			--_finish;
			
			return pos;  //还是原位置，没变
		}

		T& operator[](size_t i)
		{
			assert(i < size());
			
			return _start[i];
		}
		
		const T& operator[](size_t i) const
		{
			assert(i < size());
			
			return _start[i];
		}
	private:
		iterator _start;
		iterator _finish;  //指向最后一个元素的下一个位置
		iterator _endofstorage;
	}
	
	void test() //出错，reserve时memcpy按字节拷贝，浅拷贝，堆上空间delete _start时被释放，拷出来的string中的_str还是指向旧空间
	{
		vector<string> V;
		v.push_back("11111111");
		v.push_back("22222222");
		v.push_back("33333333");
		
		for (auto e : v)
		{
			cout << e << " ";
		}
		cout << endl;
	}
}