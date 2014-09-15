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
// darray.h
//------------------------------------------------------------------------------

#ifndef DARRAY_H_BCLIB
#define DARRAY_H_BCLIB

#include <new>
#include "helpers.h"

template<class T>
class DArrayTraits
{
public:
    static inline void assign(T * pTo, T * pFrom)
    {
        *pTo = *pFrom;
    }
};

template<class T, class U = DArrayTraits<T> >
class DArray : SMARTOBJECT
{
public:
    DArray();
    DArray(const DArray &cSource);

    virtual ~DArray();

    bool add(T & obj);
    bool at(UINT index, T & obj_out);
    bool remove(UINT index, T & obj_out);

private:
    UINT _capacity;
    UINT _size;
    T * _pContents;

    bool doubleCapacity();
};

template<class T, class U>
DArray<T, U>::DArray() :
    _capacity(16),
    _size(0)
{
    _pContents = new T[_capacity];
}

template<class T, class U>
DArray<T, U>::DArray(const DArray &cSource) :
    _capacity(cSource._capacity),
    _size(cSource._size)
{
    _pContents = new T[_capacity];

    for (UINT i = 0; i < _size; i++)
    {
        U::assign(_pContents + i, cSource._pContents + i);
    }
}

template<class T, class U>
DArray<T, U>::~DArray()
{
    delete[] _pContents;
}

template<class T, class U>
bool DArray<T, U>::add(T & obj)
{
    if (_size == _capacity && !doubleCapacity())
    {
        return false;
    }

    U::assign(_pContents + _size++, & obj);
    return true;
}

template<class T, class U>
bool DArray<T, U>::at(UINT index, T & obj_out)
{
    if (index >= _size)
    {
        return false;
    }

    U::assign(& obj_out, _pContents + index);

    return true;
}

template<class T, class U>
bool DArray<T, U>::remove(UINT index, T & obj_out)
{
    if (index >= _size)
    {
        return false;
    }

    U::assign(& obj_out, _pContents + index);

    _size--;

    for (int i = index; i < _size; i++)
    {
        U::assign(_pContents + i, _pContents + i + 1);
    }

    return true;
}

template<class T, class U>
bool DArray<T, U>::doubleCapacity()
{
    UINT newCapacity = _capacity << 1;
    T * pNewContents = new (std::nothrow) T[newCapacity];

    // Check that we were able to allocate memory
    if (!pNewContents) return false;

    for (UINT i = 0; i < _size; i++)
    {
        U::assign(pNewContents + i, _pContents + i);
    }

    delete[] _pContents;

    _pContents = pNewContents;
    _capacity = newCapacity;

    return true;
}

#endif