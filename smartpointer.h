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
 * smartpointer.h
 */
#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#ifndef NULL
#define NULL 0
#endif

#ifndef SMARTPOINTER_EXCEPTION
#define SMARTPOINTER_EXCEPTION "Cannot assign object to SmartPointer; call remove() first."
#endif

template<class T>
class SmartPointer
{
    template<class U> friend class SmartPointer;

public:
    SmartPointer() : _pObject(NULL) {}

    SmartPointer(const SmartPointer &cSource) :
        _pObject(cSource._pObject)
    {
        if (_pObject)
        {
            static_cast<SmartObject *>(_pObject)->IncReferenceCount();
        }
    }

    SmartPointer(T *pSource) :
        _pObject(pSource)
    {
        if (_pObject)
        {
            static_cast<SmartObject *>(_pObject)->IncReferenceCount();
        }
    }

    template<class U> SmartPointer(const SmartPointer<U> cSource) :
        _pObject(static_cast<T *>(cSource._pObject))
    {
        if (_pObject)
        {
            static_cast<SmartObject *>(_pObject)->IncReferenceCount();
        }
    }

    template<class U> SmartPointer(U *pSource) :
        _pObject(static_cast<T *>(pSource))
    {
        if (_pObject)
        {
            static_cast<SmartObject *>(_pObject)->IncReferenceCount();
        }
    }

    virtual ~SmartPointer()
    {
        if (_pObject && !static_cast<SmartObject *>(_pObject)->DecReferenceCount())
        {
            delete _pObject;
        }
    }

    T *remove();

    SmartPointer& operator =(const SmartPointer &cSource);
    SmartPointer& operator =(T *pSource);
    operator T *();
    T *operator ->();
    T **operator &();
    T operator *();

// Cast to/from other types
    template<class U> SmartPointer& operator =(const SmartPointer<U> &cSource);
    template<class U> SmartPointer& operator =(U *pSource);
    template<class U> operator U *();

private:
    T *_pObject;
};

template<class T>
T *SmartPointer<T>::remove()
{
    if (!_pObject)
    {
        return NULL;
    }
    static_cast<SmartObject *>(_pObject)->DecReferenceCount();
    T *pTemp = _pObject;
    _pObject = NULL;
    return pTemp;
}

template<class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer &cSource)
{
    if (_pObject)
    {
        throw SMARTPOINTER_EXCEPTION;
    }
    if (this != &cSource)
    {
        _pObject = cSource._pObject;
        if (_pObject)
        {
            static_cast<SmartObject *>(_pObject)->IncReferenceCount();
        }
    }
    return *this;
}

template<class T>
SmartPointer<T>& SmartPointer<T>::operator=(T *pSource)
{
    if (_pObject)
    {
        throw SMARTPOINTER_EXCEPTION;
    }
    _pObject = pSource;
    if (_pObject)
    {
        static_cast<SmartObject *>(_pObject)->IncReferenceCount();
    }
    return *this;
}

template<class T>
SmartPointer<T>::operator T *()
{
    return _pObject;
}

template<class T>
T *SmartPointer<T>::operator ->()
{
    return _pObject;
}

template<class T>
T **SmartPointer<T>::operator &()
{
    return &_pObject;
}

template<class T>
T SmartPointer<T>::operator *()
{
    return *_pObject;
}

#endif

template<class T>
template<class U>
SmartPointer<T>& SmartPointer<T>::operator =(const SmartPointer<U> &cSource)
{
    if (_pObject)
    {
        throw SMARTPOINTER_EXCEPTION;
    }
    _pObject = static_cast<T *>(cSource._pObject);
    if (_pObject)
    {
        static_cast<SmartObject *>(_pObject)->IncReferenceCount();
    }
    return *this;
}

template<class T>
template<class U>
SmartPointer<T>& SmartPointer<T>::operator =(U *pSource)
{
    if (_pObject)
    {
        throw SMARTPOINTER_EXCEPTION;
    }
    _pObject = static_cast<T *>(pSource);
    if (_pObject)
    {
        static_cast<SmartObject *>(_pObject)->IncReferenceCount();
    }
    return *this;
}

template<class T>
template<class U>
SmartPointer<T>::operator U *()
{
    return static_cast<U *>(_pObject);
}
