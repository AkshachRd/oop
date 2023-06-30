#pragma once
#include "MyListIterator.h"
#include <optional>

template<typename T>
class CMyList
{
    template<typename T>
    friend class CMyListIterator;
private:
    struct Node
    {
        std::optional<T> data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
        Node() : data(std::nullopt), prev(nullptr), next(nullptr) {}
    };

    int m_size;
    Node* m_head;
    Node* m_tail;
    void Swap(CMyList& other) noexcept;
public:
    using Iterator = CMyListIterator<T>;
    using ConstIterator = CMyListIterator<const T>;
    using ReverseIterator = std::reverse_iterator<Iterator>;

    CMyList();
    CMyList(const CMyList& other);
    CMyList(CMyList&& other) noexcept;
    ~CMyList();
    CMyList<T>& operator=(const CMyList<T>& other);
    CMyList<T>& operator=(CMyList<T>&& other) noexcept;

    void PushFront(const T& value);
    void PushBack(const T& value);
    Iterator begin() const;
    Iterator end() const;
    ConstIterator cbegin() const;
    ConstIterator cend() const;
    ReverseIterator rbegin() const;
    ReverseIterator rend() const;
    size_t Size() const;
    bool IsEmpty() const;
    Iterator Insert(const CMyListIterator<T>& position, const T& value);
    Iterator Erase(const CMyListIterator<T>& position);
    void Clear();
};

template<typename T>
CMyList<T>::CMyList() : m_size(0)
{
    try
    {
        m_head = new Node;
        m_tail = new Node;
        m_head->next = m_tail;
        m_tail->prev = m_head;
    }
    catch (const std::exception& error)
    {
        throw error;
    }
}

template<typename T>
CMyList<T>::CMyList(const CMyList& other) : CMyList()
{
    for (auto it = other.begin(); it != other.end(); it++)
    {
        PushBack(*it);
    }
}

template<typename T>
CMyList<T>::CMyList(CMyList&& other) noexcept : CMyList()
{
    Swap(other);
}

template<typename T>
CMyList<T>::~CMyList()
{
    Clear();
    m_head->next = nullptr;
    m_tail->prev = nullptr;
}

template<typename T>
CMyList<T>& CMyList<T>::operator=(const CMyList& other)
{
    if (this != &other)
    {
        CMyList temp(other);
        Swap(temp);
    }
    return *this;
}

template<typename T>
CMyList<T>& CMyList<T>::operator=(CMyList&& other) noexcept
{
    if (this != &other)
    {
        Clear();
        Swap(other);
    }
    return *this;
}

template<typename T>
void CMyList<T>::PushFront(const T& value)
{
    Node* newNode = new Node(value);
    newNode->prev = m_head;
    newNode->next = m_head->next;

    m_head->next = newNode;
    newNode->next->prev = newNode;

    ++m_size;
}

template<typename T>
void CMyList<T>::PushBack(const T& value)
{
    Node* newNode = new Node(value);
    newNode->prev = m_tail->prev;
    newNode->next = m_tail;

    m_tail->prev = newNode;
    newNode->prev->next = newNode;

    ++m_size;
}

template<typename T>
typename CMyList<T>::Iterator CMyList<T>::begin() const
{
    return Iterator(m_head->next);
}

template<typename T>
typename CMyList<T>::Iterator CMyList<T>::end() const
{
    return Iterator(m_tail);
}

template <typename T>
typename CMyList<T>::ConstIterator CMyList<T>::cbegin() const
{
    return ConstIterator(m_head->next);
}

template <typename T>
typename CMyList<T>::ConstIterator CMyList<T>::cend() const
{
    return ConstIterator(m_tail);
}

template<typename T>
typename CMyList<T>::ReverseIterator CMyList<T>::rbegin() const
{
    return ReverseIterator(end());
}

template<typename T>
typename CMyList<T>::ReverseIterator CMyList<T>::rend() const
{
    return ReverseIterator(begin());
}

template<typename T>
size_t CMyList<T>::Size() const
{
    return m_size;
}

template<typename T>
bool CMyList<T>::IsEmpty() const
{
    return m_size == 0;
}

template<typename T>
typename CMyList<T>::Iterator CMyList<T>::Insert(const CMyListIterator<T>& position, const T& value)
{
    Node* newNode = new Node(value);

    Node* beforeNew = position.m_node->prev;
    Node* afterNew = beforeNew->next;

    newNode->prev = beforeNew;
    newNode->next = afterNew;

    beforeNew->next = newNode;
    afterNew->prev = newNode;

    ++m_size;

    return Iterator(newNode);
}

template<typename T>
typename CMyList<T>::Iterator CMyList<T>::Erase(const CMyListIterator<T>& position)
{
    Node* beforePos = position.m_node->prev;
    Node* afterPos = position.m_node->next;

    position.m_node->prev = nullptr;
    position.m_node->next = nullptr;

    beforePos->next = afterPos;
    afterPos->prev = beforePos;

    --m_size;

    return Iterator(afterPos);
}

template<typename T>
void CMyList<T>::Clear()
{
    if (m_head->next != m_tail)
    {
        Node* node = m_head->next;
        m_head->next = m_tail;
        node->prev = nullptr;
        m_tail->prev->next = nullptr;
        delete node;

        m_size = 0;
    }
}

template<typename T>
void CMyList<T>::Swap(CMyList& other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_head, other.m_head);
    std::swap(m_tail, other.m_tail);
}