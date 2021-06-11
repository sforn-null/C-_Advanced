#pragma once
#include<iostream>
#include<vector>
using namespace std;

enum State
{
	EMPTY,
	EXITS,
	DELETE,
};

template<class T>
struct HashData
{
	T _data;
	State _state;
};

template<class K,class T,class KeyOfT>
class HashTable
{
public:
	bool Insert(const T& d)
	{
		//负载因子 = 表中数据 / 表的大小 衡量哈希表满的程度
		//表越接近满，插入数据越容易冲突，冲突越多，效率越低
		//哈希表并不是满了才增容，开放定值法中，
		//一般负载因子到了0.7左右就开始增容
		//负载因子越小，冲突的概率越低，整体效率越高，
		//但是负载因子越小，浪费的空间越大
		//所以负载因子一般取一个折中值
		if (_num * 10 / _tables.size() >= 7)
		{
			// 增容

		}
		//计算d中的key在表中的映射的位置
		KeyOfT koft;
		size_t index = d % _tables.size();
		while (_tables[index]._state == EXITS)
		{
			if (KeyOfT(_tables[index]._data) == d)
			{
				return false;
			}
			++index;
			if (index == _tables.size())
			{
				index = 0;
			}
		}
		_tables[index]._data = d;
		_tables[index]._state = EXITS;
		_num++;
		return true;
	}

	HashData* Find(const K& key)
	{
		KeyOfT koft;
		size_t index = key % _tables.size();
		while (_tables[index]._state != EMPTY)
		{
			if (koft(_tables[index]._data) == key)
			{
				if (_tables[index]._state == EXITS)
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
			return true;
		}
		else
		{
			return false;
		}
	}

private:
	vector<HashData> _tables;
	size_t _num = 0;   //存了几个有效数据
};