#pragma once
#include <iostream>
#include <exception>
#include <memory>
#include <iterator>
#include <cassert>

class CStringList;

template<typename CStringListMember, typename Data>
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
	CListIterator(CStringListMember* value);

	CStringListMember* m_pNode;
};

template <typename CStringListMember, typename Data>
CListIterator<CStringListMember, Data>::CListIterator(CStringListMember* value)
	: m_pNode(value)
{}

template <typename CStringListMember, typename Data>
bool CListIterator<CStringListMember, Data>::operator==(const CListIterator<CStringListMember, Data>& it) const
{
	return m_pNode == it.m_pNode;
}

template <typename CStringListMember, typename Data>
bool CListIterator<CStringListMember, Data>::operator!=(const CListIterator<CStringListMember, Data>& it) const
{
	return m_pNode != it.m_pNode;
}

template <typename CStringListMember, typename Data>
Data& CListIterator<CStringListMember, Data>::operator*() const
{
	return m_pNode->data.value();
}

template <typename CStringListMember, typename Data>
CListIterator<CStringListMember, Data>& CListIterator<CStringListMember, Data>::operator--()
{
	if (m_pNode->prev != nullptr)
	{
		m_pNode = m_pNode->prev;
	}
	return *this;
}

template <typename CStringListMember, typename Data>
CListIterator<CStringListMember, Data>& CListIterator<CStringListMember, Data>::operator++()
{
	if (m_pNode->next != nullptr)
	{
		m_pNode = m_pNode->next;
	}
	return *this;
}

template <typename CStringListMember, typename Data>
CListIterator<CStringListMember, Data> CListIterator<CStringListMember, Data>::operator--(int)
{
	CListIterator tmp(*this);
	--(*this);
	return tmp;
}

template <typename CStringListMember, typename Data>
CListIterator<CStringListMember, Data> CListIterator<CStringListMember, Data>::operator++(int)
{
	CListIterator tmp(*this);
	++(*this);
	return tmp;
}