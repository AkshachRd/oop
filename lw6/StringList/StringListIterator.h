#pragma once
#include <iostream>
#include <exception>
#include <memory>
#include <iterator>
#include <cassert>

class CStringList;

template<typename CMyListMember, typename Data>
class CListIterator
{
	friend class CStringList;
public:
	using iterator_category = std::bidirectional_iterator_tag;
	using difference_type = std::ptrdiff_t;
	using value_type = Data;
	using pointer = Data*;
	using reference = Data&;

	Data& operator*() const;

	bool operator==(const CListIterator& it) const;
	bool operator!=(const CListIterator& it) const;

	CListIterator& operator++();
	CListIterator& operator--();

	CListIterator operator++(int);
	CListIterator operator--(int);
private:
	CListIterator(CMyListMember* value);

	CMyListMember* m_pNode;
};

template <typename CMyListMember, typename Data>
CListIterator<CMyListMember, Data>::CListIterator(CMyListMember* value)
	: m_pNode(value)
{}

template <typename CMyListMember, typename Data>
bool CListIterator<CMyListMember, Data>::operator==(const CListIterator<CMyListMember, Data>& it) const
{
	return m_pNode == it.m_pNode;
}

template <typename CMyListMember, typename Data>
bool CListIterator<CMyListMember, Data>::operator!=(const CListIterator<CMyListMember, Data>& it) const
{
	return m_pNode != it.m_pNode;
}

template <typename CMyListMember, typename Data>
Data& CListIterator<CMyListMember, Data>::operator*() const
{
	return m_pNode->data.value();
}

template <typename CMyListMember, typename Data>
CListIterator<CMyListMember, Data>& CListIterator<CMyListMember, Data>::operator--()
{
	if (m_pNode->prev != nullptr)
	{
		m_pNode = m_pNode->prev;
	}
	return *this;
}

template <typename CMyListMember, typename Data>
CListIterator<CMyListMember, Data>& CListIterator<CMyListMember, Data>::operator++()
{
	if (m_pNode->next != nullptr)
	{
		m_pNode = m_pNode->next;
	}
	return *this;
}

template <typename CMyListMember, typename Data>
CListIterator<CMyListMember, Data> CListIterator<CMyListMember, Data>::operator--(int)
{
	CListIterator tmp(*this);
	--(*this);
	return tmp;
}

template <typename CMyListMember, typename Data>
CListIterator<CMyListMember, Data> CListIterator<CMyListMember, Data>::operator++(int)
{
	CListIterator tmp(*this);
	++(*this);
	return tmp;
}