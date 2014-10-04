//------------------------------------------------------------------------------
// C++ Brian Chau Helper Library
//
// Copyright (c) Brian Chau, 2014
//
// me@brianchau.ca
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// Author information at http://www.brianchau.ca/
//
// dynamic_array.h
//------------------------------------------------------------------------------

#ifndef DYNAMIC_ARRAY_H_BCLIB
#define DYNAMIC_ARRAY_H_BCLIB

#include <iterator>
#include <memory>
#include <new>
#include "helpers.h"

#define INITIAL_SIZE 4

namespace bclib
{

template<typename T, typename Alloc = std::allocator<T> >
class dynamic_array
{
public:
    // C++11 Container requirements
    typedef Alloc allocator_type;
    typedef typename Alloc::value_type value_type;
    typedef typename Alloc::reference reference;
    typedef typename Alloc::const_reference const_reference;
    typedef typename Alloc::difference_type difference_type;
    typedef typename Alloc::size_type size_type;

private:
    // Iterator Implementations
    class dynamic_array_iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
        friend class const_dynamic_array_iterator;
    private:
        T * _pObj;

    public:
        // C++11 Iterator type specifications
        typedef typename Alloc::difference_type difference_type;
        typedef typename Alloc::value_type value_type;
        typedef typename Alloc::reference reference;
        typedef typename Alloc::pointer pointer;
        typedef std::random_access_iterator_tag iterator_category;

        // Constructors and destructors
        dynamic_array_iterator(T * pObj) : _pObj(pObj) {}
        dynamic_array_iterator(const dynamic_array_iterator & iter) : _pObj(iter._pObj) {}
        virtual ~dynamic_array_iterator() {}

        // Arithmetic operators
        dynamic_array_iterator operator +(size_t diff) const
        {
            dynamic_array_iterator tmp(*this);
            return tmp += diff;
        }
        friend dynamic_array_iterator operator +(size_t diff, dynamic_array_iterator & iter)
        {
            dynamic_array_iterator tmp(*iter);
            return tmp += diff;
        }
        dynamic_array_iterator operator -(size_t diff) const { return operator+(-1 * diff); }
        difference_type operator-(dynamic_array_iterator & iter) const { return (difference_type)(_pObj - iter._pObj); }
        dynamic_array_iterator & operator ++() { ++_pObj; return *this; }
        dynamic_array_iterator operator ++(int) { dynamic_array_iterator tmp(*this); operator++(); return tmp; }
        dynamic_array_iterator & operator --() { --_pObj; return *this; }
        dynamic_array_iterator operator --(int) { dynamic_array_iterator tmp(*this); operator--(); return tmp; }
        dynamic_array_iterator & operator +=(size_t diff)
        {
            difference_type m = diff;
            if (m >= 0)
            {
                while (m--)
                    operator++();
            }
            else
            {
                while (m++)
                    operator--();
            }
            return *this;
        }
        dynamic_array_iterator & operator -=(size_t diff) { return operator+=(-1 * diff); }

        // Boolean operators
        bool operator ==(const dynamic_array_iterator & iter) const { return _pObj == iter._pObj; }
        bool operator !=(const dynamic_array_iterator & iter) const { return _pObj == iter._pObj; }
        bool operator <(const dynamic_array_iterator & iter) const { return (iter._pObj - _pObj) > 0; }
        bool operator >(const dynamic_array_iterator & iter) const { return (_pObj - iter._pObj) > 0; }
        bool operator <=(const dynamic_array_iterator & iter) const { return (iter._pObj - _pObj) >= 0; }
        bool operator >=(const dynamic_array_iterator & iter) const { return (_pObj - iter._pObj) >= 0; }

        // Other operators and functions
        pointer operator ->() const { return _pObj; }
        reference operator *() const { return *_pObj; }
        reference operator [](size_t n) { return _pObj[n]; }
        void swap(dynamic_array_iterator & iter)
        {
            T * pTemp = _pObj; _pObj = iter._pObj; iter._pObj = pTemp;
        }
    };

    class const_dynamic_array_iterator : public std::iterator<std::random_access_iterator_tag, T>
    {
    private:
        T * _pObj;

    public:
        // C++11 Iterator type specifications
        typedef typename Alloc::difference_type difference_type;
        typedef typename Alloc::value_type value_type;
        typedef typename Alloc::const_reference const_reference;
        typedef typename Alloc::pointer const_pointer;
        typedef std::random_access_iterator_tag iterator_category;

        // Constructors and destructors
        const_dynamic_array_iterator(T * pObj) : _pObj(pObj) {}
        const_dynamic_array_iterator(const const_dynamic_array_iterator & iter) : _pObj(iter._pObj) {}
        const_dynamic_array_iterator(const dynamic_array_iterator & iter) : _pObj(iter._pObj) {}
        virtual ~const_dynamic_array_iterator() {}

        // Arithmetic operators
        const_dynamic_array_iterator operator +(size_t diff) const
        {
            const_dynamic_array_iterator tmp(*this);
            return tmp += diff;
        }
        friend const_dynamic_array_iterator operator +(size_t diff, const_dynamic_array_iterator & iter)
        {
            const_dynamic_array_iterator tmp(*iter);
            return tmp += diff;
        }
        const_dynamic_array_iterator operator -(size_t diff) const { return operator+(-1 * diff); }
        difference_type operator-(const_dynamic_array_iterator & iter) const { return (difference_type)(_pObj - iter._pObj); }
        const_dynamic_array_iterator & operator ++() { ++_pObj; return *this; }
        const_dynamic_array_iterator operator ++(int) { const_dynamic_array_iterator tmp(*this); operator++(); return tmp; }
        const_dynamic_array_iterator & operator --() { --_pObj; return *this; }
        const_dynamic_array_iterator operator --(int) { const_dynamic_array_iterator tmp(*this); operator--(); return tmp; }
        const_dynamic_array_iterator & operator +=(size_t diff)
        {
            difference_type m = diff;
            if (m >= 0)
            {
                while (m--)
                    operator++();
            }
            else
            {
                while (m++)
                    operator--();
            }
            return *this;
        }
        const_dynamic_array_iterator & operator -=(size_t diff) { return operator+=(-1 * diff); }

        // Boolean operators
        bool operator ==(const const_dynamic_array_iterator & iter) const { return _pObj == iter._pObj; }
        bool operator !=(const const_dynamic_array_iterator & iter) const { return _pObj == iter._pObj; }
        bool operator <(const const_dynamic_array_iterator & iter) const { return (iter._pObj - _pObj) > 0; }
        bool operator >(const const_dynamic_array_iterator & iter) const { return (_pObj - iter._pObj) > 0; }
        bool operator <=(const const_dynamic_array_iterator & iter) const { return (iter._pObj - _pObj) >= 0; }
        bool operator >=(const const_dynamic_array_iterator & iter) const { return (_pObj - iter._pObj) >= 0; }

        // Other operators and functions
        const_pointer operator ->() const { return _pObj; }
        const_reference operator *() const { return *_pObj; }
        const_reference operator [](size_t n) { return _pObj[n]; }
        void swap(const_dynamic_array_iterator & iter)
        {
            T * pTemp = _pObj; _pObj = iter._pObj; iter._pObj = pTemp;
        }
    };

public:
    // Iterator typedefs
    typedef dynamic_array_iterator iterator;
    typedef const_dynamic_array_iterator const_iterator;

    // Constructors
    dynamic_array();
    dynamic_array(const dynamic_array &cSource);
    virtual ~dynamic_array();

    // Iterator Methods
    iterator begin() { return iterator(_pContents); }
    const_iterator begin() const { return const_iterator(_pContents); }
    const_iterator cbegin() const { return const_iterator(_pContents); }
    iterator end() { return iterator(_pContents + _size); }
    const_iterator end() const { return const_iterator(_pContents + _size); }
    const_iterator cend() const { return const_iterator(_pContents + _size); }

    bool add(T obj);
    bool remove(UINT index, T & obj_out);
    bool contains(T & obj) const;

    reference operator [](size_type n) { return _pContents[n]; }
    UINT _size;
private:
    //UINT _size;
    UINT _capacity;
    T * _pContents;

    bool doubleCapacity();
};

template<typename T, typename Alloc>
dynamic_array<T, Alloc>::dynamic_array() :
    _size(0),
    _capacity(INITIAL_SIZE)
{
    _pContents = new T[_capacity];
}

template<typename T, typename Alloc>
dynamic_array<T, Alloc>::dynamic_array(const dynamic_array &cSource) :
    _size(cSource._size),
    _capacity(cSource._capacity)
{
    _pContents = new T[_capacity];

    for (UINT i = 0; i < _size; i++)
    {
        *(_pContents + i) = *(cSource._pContents + i); // ALLOCATOR_ASSIGN
    }
}

template<typename T, typename Alloc>
dynamic_array<T, Alloc>::~dynamic_array()
{
    delete[] _pContents;
}

template<typename T, typename Alloc>
bool dynamic_array<T, Alloc>::add(T obj)
{
    if (_size == _capacity && !doubleCapacity())
    {
        return false;
    }

    *(_pContents + _size++) = obj; // ALLOCATOR_ASSIGN
    return true;
}

template<typename T, typename Alloc>
bool dynamic_array<T, Alloc>::remove(UINT index, T & obj_out)
{
    if (index >= _size)
    {
        return false;
    }

    obj_out = *(_pContents + index); // ALLOCATOR_ASSIGN

    _size--;

    for (int i = index; i < _size; i++)
    {
        *(_pContents + i) = *(_pContents + i + 1); // ALLOCATOR_ASSIGN
    }

    return true;
}

template<typename T, typename Alloc>
bool dynamic_array<T, Alloc>::contains(T & obj) const
{
    for (UINT i = 0; i < _size; i++)
    {
        if (_pContents[i] == obj)
        {
            return true;
        }
    }
    return false;
}

template<typename T, typename Alloc>
bool dynamic_array<T, Alloc>::doubleCapacity()
{
    UINT newCapacity = _capacity << 1;
    T * pNewContents = new (std::nothrow) T[newCapacity];

    // Check that we were able to allocate memory
    if (!pNewContents) return false;

    for (UINT i = 0; i < _size; i++)
    {
        *(pNewContents + i) = *(_pContents + i); // ALLOCATOR_ASSIGN
    }

    delete[] _pContents;

    _pContents = pNewContents;
    _capacity = newCapacity;

    return true;
}

} // namespace bclib

#endif // DYNAMIC_ARRAY_H_BCLIB
