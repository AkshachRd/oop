#pragma once
#include <optional>
#include <iostream>
#include "StringListIterator.h"

class CStringList
{
	struct CStringListMember
	{
		CStringListMember()
			: prev(nullptr), next(nullptr)
		{
		}

		CStringListMember(const std::string& data, CStringListMember* prev, CStringListMember* next)
			: data(data), prev(prev), next(next)
		{
		}

		CStringListMember(const std::string&& data, CStringListMember* prev, CStringListMember* next)
			: data(data), prev(prev), next(next)
		{
		}

		~CStringListMember()
		{
			if (!next)
			{
				delete next;
			}
			if (!prev)
			{
				delete prev;
			}

		}

		std::optional<std::string> data;

		CStringListMember* prev;
		CStringListMember* next;
	};

public:
	using Iterator = CListIterator<CStringListMember, std::string>;
	using ConstIterator = CListIterator<CStringListMember, const std::string>;

	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	CStringList();
	CStringList(const CStringList& list);
	~CStringList();

	Iterator begin();
	Iterator end();
	ConstIterator cbegin() const;
	ConstIterator cend() const;

	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstReverseIterator rcend();
	ConstReverseIterator rcbegin();
	Iterator Insert(Iterator const& pos, std::string const& data);
	Iterator Erase(Iterator const& pos);

	void PushFront(const std::string& data);
	void PushBack(const std::string& data);

	size_t GetSize() const;
	bool IsEmpty() const;

	void Clear();

	CStringList& operator=(const CStringList& rhs);
private:
	size_t m_size;

	CStringListMember* m_first;
	CStringListMember* m_last;
};

CStringList::CStringList()
	: m_size(0)
{
	try
	{
		m_first = new CStringListMember;
		m_last = new CStringListMember;
		m_first->next = m_last;
		m_last->prev = m_first;
	}
	catch (const std::exception& error)
	{
		throw error;
	}
}

CStringList::CStringList(const CStringList& list)
	: CStringList()
{
	for (auto it = list.cbegin(); it != list.cend(); it++)
	{
		PushBack(*it);
	}
}

CStringList::~CStringList()
{
	Clear();
	m_first->next = nullptr;
	m_last->prev = nullptr;
}

CStringList& CStringList::operator=(const CStringList& rhs)
{
	if (std::addressof(rhs) != this)
	{
		CStringList copy(rhs);
		std::swap(m_first, copy.m_first);
		std::swap(m_last, copy.m_last);
		std::swap(m_size, copy.m_size);
	}

	return *this;
}

void CStringList::Clear()
{
	if (m_first->next != m_last)
	{
		CStringListMember* node = m_first->next;
		m_first->next = m_last;
		node->prev = nullptr;
		m_last->prev->next = nullptr;
		delete node;

		m_size = 0;
	}
}

typename CStringList::Iterator CStringList::begin()
{
	return Iterator(m_first->next);
}

typename CStringList::Iterator CStringList::end()
{
	return Iterator(m_last);
}

typename CStringList::ConstIterator CStringList::cbegin() const
{
	return ConstIterator(m_first->next);
}

typename CStringList::ConstIterator CStringList::cend() const
{
	return ConstIterator(m_last);
}

typename CStringList::ReverseIterator CStringList::rbegin()
{
	return std::reverse_iterator<Iterator>(end());
}

typename CStringList::ReverseIterator CStringList::rend()
{
	return std::reverse_iterator<Iterator>(begin());
}

typename CStringList::ConstReverseIterator CStringList::rcbegin()
{
	return std::reverse_iterator<ConstIterator>(cend());
}

typename CStringList::ConstReverseIterator CStringList::rcend()
{
	return std::reverse_iterator<ConstIterator>(cbegin());
}

typename CStringList::Iterator CStringList::Insert(Iterator const& pos, std::string const& data)
{
	auto newNode = new CStringListMember(data, nullptr, nullptr);

	CStringListMember* beforeNew = pos.m_pNode->prev;
	CStringListMember* afterNew = beforeNew->next;

	newNode->prev = beforeNew;
	newNode->next = afterNew;

	beforeNew->next = newNode;
	afterNew->prev = newNode;

	++m_size;

	return Iterator(newNode);
}

typename CStringList::Iterator CStringList::Erase(Iterator const& pos)
{
	CStringListMember* beforePos = pos.m_pNode->prev;
	CStringListMember* afterPos = pos.m_pNode->next;

	pos.m_pNode->prev = nullptr;
	pos.m_pNode->next = nullptr;

	beforePos->next = afterPos;
	afterPos->prev = beforePos;

	--m_size;

	return Iterator(afterPos);
}

void CStringList::PushFront(const std::string& data)
{
	auto newNode = new CStringListMember(data, m_first, m_first->next);

	m_first->next = newNode;
	newNode->next->prev = newNode;

	++m_size;
}

void CStringList::PushBack(const std::string& data)
{
	auto newNode = new CStringListMember(data, m_last->prev, m_last);

	m_last->prev = newNode;
	newNode->prev->next = newNode;

	++m_size;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}