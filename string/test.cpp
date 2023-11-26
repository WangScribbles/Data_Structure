#include <iostream>
using namespace std;
//#include "source_string.h"

#include "string.h" //不能在using上面展开，否则向上找找不到cout......
//只会向上找
//没展开ws命名空间，否则冲突

int main()
{
	//ws::test_string1();
	//ws::test_string2();
	//ws::test_string3();
	//ws::test_string4();
	ws::test_string4();

	return 0;
}
