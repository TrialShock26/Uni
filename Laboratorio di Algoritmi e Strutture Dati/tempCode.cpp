#include <iostream>
#include <random>
#include <functional>
class A {
	protected:
	int a = 0;
	public:
	A() = default;
	A(int x) {a = x;}
	virtual void print() {std::cout<<"A" <<std::endl;}
};

class B: virtual public A {
	protected:
	int b;
	public:
	B() = default;
	B(int x, int y): A(x) {b = y;}
	void print() override {std::cout<<"B" <<std::endl;}
};

class C: virtual public B {
	public:
	C() = default;
	C(int x, int y): A(x), B(x, y) {}
	int getA() {return a;}
	int getB() {return b;}
	void print() override {std::cout<<"C" <<std::endl;}
};


int main() {
	ulong z = -1;
	std::cout<<z;
	std::cout<<std::endl;
	int vec[10] = {};
	vec[1] = 3;
	for (int i = 0; i < 10; i++) {
		std::cout<<vec[i] <<" ";
	}
	std::cout<<std::endl;
	std::swap(vec[1], vec[9]);
	for (int i = 0; i < 10; i++) {
		std::cout<<vec[i] <<" ";
	}
	std::cout<<std::endl;
	C c(2, 3);
	std::cout<<c.getA() <<c.getB();
	std::cout<<std::endl;
	B b;
	b.print();
	c.print();
	std::cout<<std::endl;
	B* e = &c;
	e->print();
	std::cout<<std::endl;
	std::string x("A"), y("B");
	if (x>y) std::cout<<true;
	else std::cout<<false;
	return 0;
}
