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
    void qux()
    {
        printf("Method Call!      0x%016llx\n", (ULL)(this));
    }
};

class Bar : public Foo
{
public:
    Bar() : Foo() { printf("\t -> From Bar\n"); }
    Bar(const Bar &copy) : Foo(copy) { printf("\t -> From Bar\n"); }
    virtual ~Bar() { printf("Bar: "); }
};

class Lol : SMARTOBJECT
{

};

int main()
{
    SmartPointer<Foo> spFoo1(new Foo()); // equivalent to spFoo1 = new Foo()
    SmartPointer<Foo> spFoo2(spFoo1);
    spFoo1->qux();
    spFoo2->qux();
    Foo foo = *spFoo1;
    SmartPointer<Foo> spFoo3(new Foo(*spFoo2)); // Copy Constructor invoked*/
    SmartPointer<Foo> spFoo4(new Bar());
    SmartPointer<Bar> spBar1(spFoo4);
    Bar bar = *spBar1;

    Foo *pFoo = spBar1;
    SmartPointer<Bar> spBar2 = pFoo;

    SmartPointer<Lol> spLol1(new Lol());
    //SmartPointer<Bar> spBar2 = spLol1; // This line won't work

    return 0;
}
