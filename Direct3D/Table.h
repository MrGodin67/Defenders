#pragma once
#include <cassert>
#include <vector>

template <typename T>
class Table
{
private:
	int m_Rows;
	int m_Columns;
	std::vector<T> m_Container;
public:
	Table()
		: m_Rows(0), m_Columns(0)
	{
	}

	Table(int m, int n)
		: m_Rows(m), m_Columns(n), m_Container(m*n)
	{
	}

	Table(int m, int n, const T& value)
		: m_Rows(m), m_Columns(n), m_Container(m*n, value)
	{
	}


	T& operator()(int i, int j)
	{
		return m_Container[i*m_Columns + j];
	}


	const T& operator()(int i, int j)const
	{
		return m_Container[i*m_Columns + j];
	}
	const T& operator()(int index)const
	{
		return m_Container[index];
	}

	typedef typename std::vector<T>::iterator iter;
	typedef typename std::vector<T>::const_iterator citer;


	iter begin() { return m_Container.begin(); }
	iter end() { return m_Container.end(); }


	citer begin() const { return m_Container.begin(); }
	citer end() const { return m_Container.end(); }

	int numRows() const { return m_Rows; }
	int numCols() const { return m_Columns; }
	size_t numElements()const { return m_Container.size(); }
	void resize(int m, int n)
	{
		m_Rows = m;
		m_Columns = n;
		m_Container.resize(m*n);
	}

	void resize(int m, int n, const T& value)
	{
		m_Rows = m;
		m_Columns = n;
		m_Container.resize(m*n, value);
	}


};
