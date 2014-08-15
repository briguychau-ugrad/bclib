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
 * smartobject.h
 */
#ifndef SMARTOBJECT_H
#define SMARTOBJECT_H

#define UINT unsigned int
#define SMARTOBJECT public virtual SmartObject

class SmartObject
{
public:
    virtual ~SmartObject() {}

    UINT IncReferenceCount();
    UINT DecReferenceCount();

    UINT GetReferenceCount() const { return _refcount; }

protected:
    SmartObject() : _refcount(0) {}
    SmartObject(const SmartObject& cSource) : _refcount(0) {}

private:
    UINT _refcount;
};

#endif
