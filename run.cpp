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
 * run.h
 */
#include "smart.h"

#include <stdio.h>

#define ULL unsigned long long

class Foo : SMARTOBJECT
{
public:
    Foo() : SmartObject()
    {
        printf("Constructor!      0x%016llx\n", (ULL)(this));
    }
    Foo(const Foo &copy) : SmartObject(copy)
    {
        printf("Copy Constructor! 0x%016llx\n", (ULL)(this));
    }
    virtual ~Foo()
    {
        printf("Destructor!       0x%016llx\n", (ULL)(this));
    }
    void bar()
    {
        printf("Method Call!      0x%016llx\n", (ULL)(this));
    }
};

int main()
{
    SmartPointer<Foo> spFoo1(new Foo()); // equivalent to spFoo1 = new Foo()
    SmartPointer<Foo> spFoo2(spFoo1);
    spFoo1->bar();
    spFoo2->bar();
    Foo foo = *spFoo1;
    SmartPointer<Foo> spFoo3(new Foo(*spFoo2)); // Copy Constructor invoked
    return 0;
}
