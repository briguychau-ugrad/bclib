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
        printf("Foo: Constructor!      0x%016llx\n", (ULL)(this));
    }
    Foo(const Foo &copy) : SmartObject(copy)
    {
        printf("Foo: Copy Constructor! 0x%016llx\n", (ULL)(this));
    }
    virtual ~Foo()
    {
        printf("Foo: Destructor!       0x%016llx\n", (ULL)(this));
    }
    void qux() const
    {
        printf("Foo: Method Call!      0x%016llx\n", (ULL)(this));
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
public:
    Lol() : SmartObject()
    {
        printf("Lol: Constructor!      0x%016llx\n", (ULL)(this));
    }
    Lol(const Lol &copy) : SmartObject(copy)
    {
        printf("Lol: Copy Constructor! 0x%016llx\n", (ULL)(this));
    }
    virtual ~Lol()
    {
        printf("Lol: Destructor!       0x%016llx\n", (ULL)(this));
    }
    void baz() const
    {
        printf("Lol: Method Call!      0x%016llx\n", (ULL)(this));
    }
};

class Hai : public Foo, public Lol
{
public:
};

void TestMethod01()
{
    printf("Begin Test Method 01\n");

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

    printf("End Test Method 01\n");
}

void TestMethod02()
{
    printf("Begin Test Method 02\n");

    SmartPointer<Foo> spFoo1(new Hai());
    SmartPointer<Hai> spHai1(spFoo1);
    SmartPointer<Lol> spLol1(spHai1);

    SmartPointer<SmartObject> spSO1(spLol1);

    printf("End Test Method 02\n");
}

void TestMethod03()
{
    printf("Begin Test Method 03\n");

    SmartArray<int> array;
    int x = 6;
    array.add(x);

    printf("End Test Method 03\n");
}

int main()
{
    TestMethod01();
    TestMethod02();
    TestMethod03();
    return 0;
}