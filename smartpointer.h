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

#include <exception>

#ifndef NULL
#define NULL 0
#endif 

template<class T>
class SmartPointer
{
public:
    SmartPointer();
    SmartPointer(T *pObject);
    SmartPointer(const SmartPointer &cSource);

    virtual ~SmartPointer();

    T *remove();

    SmartPointer& operator =(const SmartPointer &cSource);
    SmartPointer& operator =(T *pSource);
    operator T *();
    T *operator ->();
    T **operator &();
    T operator *();

private:
    T *_pObject;
};

extern class SMART_POINTER_ALREADY_ASSIGNED : public std::exception
{
public:
    virtual const char* what() const throw()
    {
        return "Cannot assign object to SmartPointer; call remove() first.";
    }
} already_assigned;

template<class T>
SmartPointer<T>::SmartPointer() :
    _pObject(NULL)
{}

template<class T>
SmartPointer<T>::SmartPointer(T *pObject) :
    _pObject(pObject)
{
    if (_pObject)
    {
        static_cast<SmartObject *>(_pObject)->IncReferenceCount();
    }
}

template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer &cSource) :
    _pObject(cSource._pObject)
{
    if (_pObject)
    {
        static_cast<SmartObject *>(_pObject)->IncReferenceCount();
    }
}

template<class T>
SmartPointer<T>::~SmartPointer()
{
    if (_pObject && !static_cast<SmartObject *>(_pObject)->DecReferenceCount())
    {
        delete _pObject;
    }
}

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
        throw already_assigned;
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
        throw already_assigned;
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
