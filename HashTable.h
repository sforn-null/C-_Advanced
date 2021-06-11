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
		//�������� = �������� / ��Ĵ�С ������ϣ�����ĳ̶�
		//��Խ�ӽ�������������Խ���׳�ͻ����ͻԽ�࣬Ч��Խ��
		//��ϣ���������˲����ݣ����Ŷ�ֵ���У�
		//һ�㸺�����ӵ���0.7���ҾͿ�ʼ����
		//��������ԽС����ͻ�ĸ���Խ�ͣ�����Ч��Խ�ߣ�
		//���Ǹ�������ԽС���˷ѵĿռ�Խ��
		//���Ը�������һ��ȡһ������ֵ
		if (_num * 10 / _tables.size() >= 7)
		{
			// ����

		}
		//����d�е�key�ڱ��е�ӳ���λ��
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
	size_t _num = 0;   //���˼�����Ч����
};