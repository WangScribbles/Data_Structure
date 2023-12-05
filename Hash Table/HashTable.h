// 哈希冲突：不同的值映射到了相同的位置

// 开放定址法（闭散列）：
// 1.线性探测 2.二次探测

#pragme once
#include <vector>

enum State
{
	EMPTY, 
	EXIST,
	DELETE,
};

template<class K>
struct HashData
{
	K _data;
	State _state = EMPTY;
};

template<class K>
class HashTable
{
public:
	bool Insert(const K& key)
	{
		// 负载因子 = 表中数据个数 / 表的大小  （衡量哈希表满的程度）
		// 表接近满，插入的数据越容易冲突，冲突越多，效率越低
		// 哈希表并不是满了才增容。开放定址法中，一般负载因子到了0.7左右开始增容
		// 负载因子越小，冲突概率越低，整体效率越高，但是负载因子越小，浪费的空间越大
		// 所以负载因子一般取一个折中值
		if (_tables.size() == 0 || _num * 0.1 / _tables.size() >= 0.7)
		{
			// 增容
			// 1.开一个2倍的空间
			// 2.遍历旧表，将旧表中的数据重新映射到新表
			// 3.释放旧表的空间
			
			/*
			{
				vector<HashData> newtables;
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				newtables.resize(newSize);
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					if (_tables[i]._state == EXIST)
					{
						// 计算在新表中的位置并处理冲突
						size_t index = _tables[i]._data % newtables.size();
						while (newtables[index]._state == EXITS)
						{
							++index;
							if (index == _tables.size())
								index = 0;
						}
						
						newtables[index] = _tables[i];
					}
				}
				
				_tables.swap(newtables);
			}
			*/
			
			HashTable<K> newHt;
			size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
			newHt._tables.resize(newSize);
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i]._state == EXIST)
				{
					newHt.Insert(_tables[i]._data);
				}
			}
			_tables;
			_tables.swap(newHt._tables);
		}
		
		
		// 计算d在表中映射的位置
		size_t index = key % _tables.size();
		
		//线性探测
		while (_tables[index]._state == EXIST)
		{
			if (_tables[index]._data == key)
			{
				return false;
			}
			
			++index;
			if (index == _tables.size())
			{
				index = 0;
			}
		}
		
		_tables[index]._data = key;
		_tables[index]._state = EXIST;
		_num++;
		
		return true;
	}
	
	HashData* Find(const K& key)
	{
		// 计算d在表中映射的位置
		size_t index = key % _tables.size();
		while (_tables[index]._state != EMPTY)
		{
			if (_tables[index]._data == key)
			{
				if (_tables[index]._state == EXIST)
				{
					return &_tables[index];
				}
				else if (_tables[index]._state == DELETE)
				{
					return nullptr;
				}
			}
			
			++index;
			if (index == _tables.size())
			{
				index = 0;
			}
		}
		
		return nullptr;
	}
	
	bool Erase(const K& key)
	{
		HashData* ret = Find(key);
		if (ret)
		{
			ret->_state = DELETE;
			--_num;
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	vector<K> _tables;
	size_t _num = 0; // 存了几个有效数据
}

void TestHashTable()
{
	HashTable<int> ht;
	ht.Insert(4);
	ht.Insert(14);
	ht.Insert(24);
	ht.Insert(5);
	ht.Insert(15);
	ht.Insert(25);
	ht.Insert(6);
	ht.Insert(16);
	ht.Insert(26);
}