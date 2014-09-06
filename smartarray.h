/**
 * C++ Smart Object Library
 *
 * Copyright (c) Brian Chau, 2014
 *
 * me@brianchau.ca
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Author information at http://www.brianchau.ca/
 *
 * smartarray.h
 */
#ifndef SMARTARRAY_H
#define SMARTARRAY_H

#include <algorithm>
#include <cstdio>
#include <cstdlib>

#ifndef NULL
#define NULL 0
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef UINT
#define UINT unsigned int
#endif

template<class T>
class SmartArray
{
public:
    SmartArray();

    virtual ~SmartArray()
    {
        for (UINT i = 0; i < _size; i++)
        {
            (_pContents + i)->~T();
        }

        std::free(_pContents);
    }

    bool add(T & obj);
    T * at(UINT index);
    T * remove(UINT index);

private:
    UINT _capacity;
    UINT _size;
    T * _pContents;

    bool doubleCapacity();
};

template<class T>
SmartArray<T>::SmartArray() :
    _capacity(8),
    _size(0)
{
    _pContents = (T *) std::malloc(_capacity * sizeof(T));
}

template<class T>
bool SmartArray<T>::add(T & obj)
{
    if (_capacity == _size && !doubleCapacity())
    {
        return false;
    }
    new(_pContents + _size) T(obj);

    // Keep a reference count of at least 1 for all objects in the array,
    // since a SmartPointer may point to an object in here
    static_cast<SmartObject *>(_pContents + _size++)->IncReferenceCount();

    return true;
}

template<class T>
T * SmartArray<T>::at(UINT index)
{
    if (index >= _size)
    {
        return NULL;
    }

    return _pContents + index;
}

template<class T>
T * SmartArray<T>::remove(UINT index)
{
    if (index >= _size)
    {
        return NULL;
    }
    
    // TODO remove item from the array
    return _pContents + index;
}

template<class T>
bool SmartArray<T>::doubleCapacity()
{
    UINT newCapacity = _capacity << 1;
    T * pNewContents = (T *) std::malloc(newCapacity * sizeof(T));

    if (pNewContents == NULL)
    {
        // unable to allocate memory
        return false;
    }

    for (UINT i = 0; i < _capacity; i++)
    {
        new(pNewContents + i) T(_pContents[i]);
        static_cast<SmartObject *>(pNewContents + i)->IncReferenceCount();
    }

    std::free(_pContents);

    _pContents = pNewContents;
    _capacity = newCapacity;

    return true;
}

#endif