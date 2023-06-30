#pragma once
#include <iterator>

template<typename T>
class CMyList;

template<typename T>
class CMyListIterator
{
    template<typename T>
    friend class CMyList;
private:
    typename CMyList<T>::Node* m_node;

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;

    CMyListIterator(typename CMyList<T>::Node* node);

    T& operator*() const;

    CMyListIterator& operator++();
    CMyListIterator operator++(int);

    CMyListIterator& operator--();
    CMyListIterator operator--(int);

    bool operator==(const CMyListIterator& other) const;
    bool operator!=(const CMyListIterator& other) const;
};

template<typename T>
CMyListIterator<T>::CMyListIterator(typename CMyList<T>::Node* node) : m_node(node) {}

template<typename T>
T& CMyListIterator<T>::operator*() const
{
    return m_node->data.value();
}

template<typename T>
CMyListIterator<T>& CMyListIterator<T>::operator++()
{
    if (m_node->next != nullptr)
    {
        m_node = m_node->next;
    }
    return *this;
}

template<typename T>
CMyListIterator<T> CMyListIterator<T>::operator++(int)
{
    CMyListIterator<T> temp = *this;
    ++(*this);
    return temp;
}

template<typename T>
CMyListIterator<T>& CMyListIterator<T>::operator--()
{
    if (m_node->prev != nullptr)
    {
        m_node = m_node->prev;
    }
    return *this;
}

template<typename T>
CMyListIterator<T> CMyListIterator<T>::operator--(int)
{
    CMyListIterator<T> temp = *this;
    --(*this);
    return temp;
}

template<typename T>
bool CMyListIterator<T>::operator==(const CMyListIterator& other) const
{
    return m_node == other.m_node;
}

template<typename T>
bool CMyListIterator<T>::operator!=(const CMyListIterator& other) const
{
    return m_node != other.m_node;
}