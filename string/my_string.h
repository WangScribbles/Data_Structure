#include <cstring>
#include <assert>

namespace ws
{
	//实现一个支持增删查改的string
	class string
	{
	public:
		typedef char* iterator;
		
		iterator begin()
		{
			return _str;
		}
		
		iterator end()
		{
			return _str + _size; //'\0'地址
		}
		
		//默认和有参合起来
		string (char* str = "")
		{
			_size =strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1]; //多开的一个空间给'\0'，但总容量不加它
			strcpy(_str, str);
		}
		
		//现代写法
		{
			void swap(string& s)
			{
				::swap(_str, s._str);
				::swap(_size, s._size);
				::swap(_capacity, s._capacity);
				
			}
			
			//拷贝构造（深拷贝）
			string(const string& s)
				：_str(nllptr)
				,_size(0)
				,_capacity(0)
			{
				string tmp(s._str);
				this->swap(tmp);
			}
			
			//赋值（深拷贝）,返回值支持连续赋值
			string& operator=(string s)
			{
				this->swap(s);
				
				return *this;
			}
		}
		
		//析构
		~string()
		{
			_size = _capacity = 0;
			delete[] _str;
			_str = nullptr;
		}
		
		//size()
		size_t size() const
		{
			return _size;
		}
		
		//capacity()
		size_t capacity() const
		{
			return _capacity;
		}
		
		//c_str()
		const char* c_str()
		{
			return _str;
		}
		
		//重载[]
		char& operator[](size_t i)
		{
			assert(i < _size);
			
			return _str[i];
		}
		const char& operator[](size_t i) const
		{
			assert(i < _size);
			
			return _str[i];
		}
		
		//reserve()
		void reserve(size_t n)
		{
			if (n > _capacity)
			{
				char* newStr = new char[n + 1];
				strcpy(newStr, _str);
				delete[] _str;
				_str = newStr;
				_capacity = n;
			}
		}
		
		//push_back()
		void push_back(char ch)
		{
			//空间满了增容
			if (_size == _capacity)
			{
				size_t newCapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newCapacity);
			}
			
			_str[_size] = ch;
			++_size; 
			
			_str[_size] = '\0';  //插入一个增容字符时，'\0'被覆盖，最后产生随机值
		}
		
		//resize()
		void resize(size_t n, char ch = '\0') //融合std::string中的两个resize()
		{
			if (n < _size)
			{
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				if (n > _capacity)
				{
					reserve(n);
				}
				
				for (size_t i = _size; i < n; ++i)
				{
					_str[i] = ch;
				}
				_size = n;
				_str[_size] = '\0';	
			}
		}
		
		
		//append()
		void append(consst char* str)
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				size_t newCapacity = _size + len; //不能增2倍，因为可能不够（原字符2，增加的字符30，开2倍是4）
				reserve(newCapacity);
			}
			
			strcpy(_str + _size, str);
			_size += len;
		}
		
		//insert()
		string& insert(size_t pos, char ch) //std::string中没有
		{
			assert(pos <= _size);
			
			if (_size == _capacity)
			{
				size_t newCapacity = _capacity == 0 ? 2 : _capacity * 2;
				reserve(newCapacity);
			}
			
			int end = _size;
			while (end >= pos)
			{
				_str[end + 1] = _str[end];
				--end;
			}
			_str[pos] = ch;
			++_size;
			
			return *this;
		}
		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			
			//1.空间不够增容
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}
			
			//2.挪数据
			int end = size;
			while (end >= (int)pos)  //若pos是0 ，pos是size_t,end也转为size_t,死循环
			{
				_str[end + len] = _str[end]; 
				--end;
			}
			
			//3.放数据
			strncpy(_str + pos, str, len); //strcpy会把'\0'拷过去覆盖原来的一个字符
			
			_size += len;
			
			return *this;
		}
		
		//erase()
		string& erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);
			
			if (len >=_size - pos)
			{
				_str[pos[ = '\0';
				_size = pos;
			}
			else
			{
				size_t i = pos + len;
				while (i <= _size)
				{
					_str[pos] = str[i];
					++pos;
					++i;
				}
				
				_size -= len;
			}
		
			return *this;
		}
		
		//find()
		size_t find(char ch, size_t pos = 0)
		{
			for (size_t i = pos; i< _size; i++)
			{
				if (_str[i] == ch)
					return i;
			}
			
			return npos;
		}
		size_t find(const char* str, size_t pos = 0)
		{
			char* p = strstr(_str, str);
			if (p == nullptr)
			{
				return npos;
			}
			else
			{
				return p - _str;
				
			}
		}
		
		//重载比较运算符
		bool operator<(const string& s)
		{
			int ret = strcmp(_str, s._str);
			
			return ret < 0;
		}
		
		//重载+=
		string& operator+=(char ch)
		{
			this->push_back(ch);
			return *this;
		}
		
		string& operator+=(const char* str)
		{
			this->append(str);
			return *this;
		}
		
	private:
		char*  _str;
		size_t _size;
		size_t _capacity;  //表示能存的有效字符个数，'\0'不是有效字符
		
		static size_t npos;
	};
	
	size_t string::npos = -1;
	
	//普通函数重载operator<< >>
	istream& operator>>(istream& in, string& s)
	{
		char ch;
		while(1)
		{
			char ch;
			//in >> ch;  //编译器实现的输入字符，和此函数重载>>输入string类形成重载。ch接收不到' ' || '\n' || '\t'
			ch = in.get();
			
			
			//拓展：getline模拟实现：
			//ch = in.get();
			//if (ch == '\n')
			//{
			//	//...
			//}
			
			
			if (ch == ' ' || ch == '\n' || ch == '\t')
				break;
			else
				s += ch;
		}
		
		return in;
	}
	
	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			cout << s[i]; //重载[]后不需要友元
		}			
		
		return out;
	}
	
	//测试
	void test_string1()
	{
		string s1("hello");
		string s2;
		
		cout << s1 << endl;
		cout << s2 << endl;
		
		cout << s1.c_str() << endl;
		cout << s2.c_str() << endl;
		
		//三种遍历方式
		for (size_t i = 0;i < s2.size(); i++)
		{
			//...
		}
		
		string::iterator it2 = s2.begin();
		while (it2 != s2.end())
		{
			//...
		}
		
		//范围for由迭代器支持的，也就是说这段代码最终会被编译器替换成迭代器
		//若把上面的begin()或end()函数名字改了，则就不支持范围for了
		for (auto ch : s)
		{
			//...
		}
	}
	
	//增
	void test_string2()
	{
		string s("hello");
		
		s.push_back('1');
		s.append("23456");
		s += "+++"
		cout << s << endl;
	}
	
	void test_string3()
	{
		string s1("hello");
		s1.insert(1, 'x');
		s1.insert(1, 'yz');
		//cout << s1 << endl;
		
		
		
		string s2("hello");
		s2.reserve(10);
		cout << s2.size() << endl;
		cout << s2.capacity() << endl << endl;
		
		s2.resize(8, 'z');
		cout << s2.size() << endl;
		cout << s2.capacity() << endl << endl;
		
		s2.resize(18, 'a');
		cout << s2.size() << endl;
		cout << s2.capacity() << endl << endl;
	}
	
	//删
	void test_string4()
	{
		string s("helloworld");
		
		s.erase(5, 2);
		cout << s << endl;
	}
	
	//查找
	void test_string5()
	{
		string s("helloworld");
		
		
		cout << s.find('e'); << endl;
		cout << s.find('llo'); << endl;
	}
}


//深拷贝现代写法
namespace ws_copy
{
	class string
	{
	public:
		//默认和有参构造
		string(const char* str = "")
			:_str(new char[strlen(str) + 1])
		{
			
			strcpy(_str, str);
		}
		
		
		//传统写法
		{
			//拷贝构造（深拷贝）
			string(const string& s)
				:_str(new char[strlen(s._str) + 1]);
			{
				strcpy(_str, s._Str);
			}
			
			//赋值（深拷贝）
			string& operator=(const string& s)
			{
				if (this != &s)
				{
					char* tmp = new char[strlen(s._str) + 1];
					strcpy(tmp, s._Str);
					delete[] _str;
					_str = tmp;
				}
				
				return *this;
			}
		}
		
		//现代写法
		{
			//拷贝构造（深拷贝）
			string(const string& s)
				:_str(nullptr)
			{
				string tmp(s._str);
				swap(_str, tmp._str);
			}
		
			//法一：赋值（深拷贝）
			string& operator=(const string& s)
			{
				if (this != &s)
				{
					string tmp(s);
					swap(_str. tmp);
				}
				
				return *this;
			}
			
			//法二：赋值（深拷贝）
			string& operator=(string s) //传值调用深拷贝构造
			{
				swap(_str, s._str);
				return *this;
			}
		}
		
		
		
		~string
		{
			delete[] _str;
			_str = nullptr;	
		}
	private:
		char* _str;
	};
}
