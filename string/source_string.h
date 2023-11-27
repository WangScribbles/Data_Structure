#include <cstring>
 
namespace ws
{
	class string
	{
	public:
	
	
		{
			//默认构造
				/*
				 *std::string遍历时什么都不输出
				 *遍历时空指针出错
				string()
					:_str(nullptr)
				{}
				*/
			
			string()
				:_str(new char[1])
			{
				_str[0] = '\0';
			}
		
			//有参构造
				/*
				 *str是存放在代码段，不能被修改和扩容
				 *若扩容和返回[]引用后修改则错误
				 *解决方法：将字符串拷贝到堆区
				 
				string(char* str)
					:_str(str)
				{}
				*/
				
			string(char* str)
				:_str(new char[strlen(str) + 1]) //string类中有c_str这个接口，最后要符合c的习惯加个'\0'
			{
				strcpy(_str, str); //strcpy会把'\0'拷过去
			}
	
		}
	
		
		//默认和有参合起来
		string (char* str = "")  //不能给空，否则默认构造时strlen(nullptr)出问题
			:_str(new char[strlen(str) + 1])
		{
			strcpy(_str, str);
		}
		
		//拷贝构造（深拷贝）
		string(const string& s)
		:_str(new char[strlen(s._str) + 1])
		{
			strcpy(_str, s._str);
		}
		
		
		//赋值（深拷贝）,返回值支持连续赋值
		string& operator=(const string& s)
		{
			//防止自己给自己赋值
			if (this != &s)
			{
				//要把左操作符原空间释放，否则存在内存泄漏
				char* tmp = new char[strlen(s._str) + 1];  //开空间
				strcpy(tmp, s._str); //拷数据
				delete[] _str;  //释放旧空间
				_str = tmp; //指向新空间
			}
			
			return *this;
		}
		
		
		//析构
		~string()
		{
			delete[] _str;
			_str = nullptr;
		}
		
		//size()
		size_t size()
		{
			return strlen(_str);
		}
		
		//c_str()
		const char* c_str()
		{
			return _str;
		}
		
		//重载[]
		char& operator[](size_t i)
		{
			return _str[i];
		}
		
	private:
		char* _str;
		
	};
	
	//有参和无参构造
	void test_string1()
	{
		string s1("hello");
		string s2;
		
		//遍历s1
		for (size_t i = 0; i < s1.size(); i++)
		{
			s1[i] += 1;
			cout << s1[i] << " ";
		}
		cout << endl;
		
		//遍历s2
		for (size_t i = 0; i < s2.size(); i++)
		{
			s2[i] += 1;
			cout << s2[i] << " ";
		}
		cout << endl;
	}
	
	//拷贝构造 + 赋值（深拷贝）
	void test_string2()
	{
		string s1("hello");
		string s2(s1)；  //编译器自动生成的是浅拷贝，同一块空间释放两次出错
		string s3;
		s3 = s1;
		
		cout << s1.c_str() << endl; //先不重载<<
		cout << s2.c_str() << endl;
	}
}
