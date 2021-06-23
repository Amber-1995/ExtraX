#pragma once
#ifndef _XX_TABLE_H_
#define _XX_TABLE_H_

#include <memory>
#include <vector>

namespace XX
{
	template<class T>
	class XXTable
	{
	private:
		struct _Unit
		{
			bool is_using = false;
			T data = { 0 };
		};
		typedef typename std::shared_ptr<_Unit> _UnitPtr;

	public:
		const int& width;
		const int& length;

		XXTable(int table_length):
			width(_width),
			length(_length),
			_width(0),
			_length(table_length)
		{
			_NewColumn();
		}

		void Add(T data)
		{
			for (int i = 0; i < _width; i++)
			{
				for (int j = 0; j < _length; j++)
				{
					if (!(_table_header[i].get()[j].is_using))
					{
						_table_header[i].get()[j].is_using = true;
						_table_header[i].get()[j].data = data;
						return;
					}
				}
			}
			_NewColumn();
			_table_header[_width - 1].get()[0].data = data;
			_table_header[_width - 1].get()[0].is_using = true;
		}

		void Remove(T data)
		{
			for (int i = 0; i < _width; i++){

				for (int j = 0; j < _length; j++){

					if (_table_header[i].get()[j].data == data){

						_table_header[i].get()[j].is_using = false;
						return;
					}
				}
			}
		}

		_Unit GetUnit(int x, int y)
		{
			return _table_header[x].get()[y];
		}

	private:
		int _width;
		int _length;

		std::vector<_UnitPtr> _table_header;

		void _NewColumn()
		{
			_UnitPtr new_column(new _Unit[_length]);
			_table_header.push_back(new_column);
			_width++;
		}
	};
}




#endif // !_XX_TABLE_H_
