#if defined(WARMUP) + defined(EXACTMATCH) + defined(ARGNUMBERS) + defined(DEFAULTARGS) + defined(STATICMEMBER) + defined(CONSTMEMBER) + defined(VIRTUALMEMBER) + defined(TEMPLATEFUNCS) + defined(TEMPLATEMEMBER) != 1
#error need exactly one of WARMUP|EXACTMATCH|ARGNUMBERS|DEFAULTARGS|STATICMEMBER|CONSTMEMBER|VIRTUALMEMBER|TEMPLATEFUNCS|TEMPLATEMEMBER defined e.g. with -D<def>
#endif


/// ---------------------------------------------------------------------------
/// warm up
/// ---------------------------------------------------------------------------

#ifdef WARMUP
#include <iostream>

void print(int a) { std::cout << "int" << std::endl; }
void print(float b) { std::cout << "float" << std::endl; }
void print(char c) { std::cout << "char" << std::endl; }

int main() {
	float c = 1u;
	print(c);

}
#endif


/// ---------------------------------------------------------------------------
/// exact match, promotion and conversion
/// ---------------------------------------------------------------------------

#ifdef EXACTMATCH
#include <iostream>

void print(char c) { std::cout << "char" << std::endl; }
void print(int a) { std::cout << "int" << std::endl; }
void print(double b) { std::cout << "double" << std::endl; }

int main( ) {
	char c = 1;
	print(c);

	short s = 1;
	print(s);
	float f = 1;
	print(f);

	long long ll = 1;
	print(ll);
	long double ld = 1;
	print(ld);

}
#endif

/// ---------------------------------------------------------------------------
/// differing argument numbers
/// ---------------------------------------------------------------------------

#ifdef ARGNUMBERS
#include <iostream>

void print(int a) { std::cout << "1" << std::endl; }
void print(int a, int b) { std::cout << "2" << std::endl; }
void print(int a, int b, int c = 0) { std::cout << "3" << std::endl; }

int main( ) {
	print(1);
	print(1, 1);
	print(1, 1, 1);

}
#endif


/// ---------------------------------------------------------------------------
/// default arguments
/// ---------------------------------------------------------------------------

#ifdef DEFAULTARGS
#include <iostream>

void print(long a, int b = 0) { std::cout << "long" << std::endl; }
void print(double a, int b = 0) { std::cout << "double" << std::endl; }
void print(float a, int b) { std::cout << "float" << std::endl; }

int main() {
	print(1.f);
	print(1.f, 'c');

}
#endif


/// ---------------------------------------------------------------------------
/// static member functions
/// ---------------------------------------------------------------------------

#ifdef STATICMEMBER
#include <iostream>

struct A {
	static void print(long a, int b = 0) { std::cout << "static long" << std::endl; }
	static void print(float a, int b) { std::cout << "static float" << std::endl; }

	void print(double a, int b = 0) { std::cout << "double" << std::endl; }
	void print(float a, int b) { std::cout << "float" << std::endl; }
};

int main( ) {
	A::print(1.f);
	A().print(1.f, 'c');

}
#endif


/// ---------------------------------------------------------------------------
/// const member functions
/// ---------------------------------------------------------------------------

#ifdef CONSTMEMBER
#include <iostream>

struct A {
	void print(long a, int b = 0) const { std::cout << "const long" << std::endl; }
	void print(double a, int b = 0) const { std::cout << "const double" << std::endl; }

	void print(double a, int b = 0) { std::cout << "double" << std::endl; }
	void print(float a, int b) { std::cout << "float" << std::endl; }
};

int main( ) {
	A().print(1.f);
	A().print(1.f, 'c');
	A().print(1l, 1);
	const A cA;
	cA.print(1.f, 'c');

}
#endif


/// ---------------------------------------------------------------------------
/// virtual member functions
/// ---------------------------------------------------------------------------

#ifdef VIRTUALMEMBER
#include <iostream>

struct A {
	void print(int a) { std::cout << "A int" << std::endl; }
	virtual void print(char c) { std::cout << "A char" << std::endl; }
	void print(float b) { std::cout << "A float" << std::endl; }
};

struct B : A {
	void print(int a) { std::cout << "B int" << std::endl; }
	void print(char c) { std::cout << "B char" << std::endl; }
	virtual void print(float b) { std::cout << "B float" << std::endl; }
};

int main( ) {
	A a; A* ap = &a;
	B b; B* bp = &b;
	
	ap->print(1);
	bp->print(1);

	A* ba = bp;
	ba->print(1);
	ba->print('1');
	ba->print(1.f);

}
#endif


/// ---------------------------------------------------------------------------
/// template functions
/// ---------------------------------------------------------------------------

#ifdef TEMPLATEFUNCS
#include <iostream>

template<typename T1, typename T2> void print (T1 a, T2 b) { std::cout << "generic" << std::endl; }
template<typename T2> void print (char a, T2 b)            { std::cout << "specialized" << std::endl; }
template<> void print (int a, int b)                       { std::cout << "int" << std::endl; }
template<> void print (float a, float b)                   { std::cout << "float" << std::endl; }
template<> void print (char a, char b)                     { std::cout << "char" << std::endl; }

int main( ) {
	print('1', '1');
	print('1', 1.f);
	print(1, '1');

}
#endif


/// ---------------------------------------------------------------------------
/// template member functions
/// ---------------------------------------------------------------------------

#ifdef TEMPLATEMEMBER
#include <iostream>

template<class T> struct A {
	static void print (T a) { std::cout << "base" << std::endl; }
};

template<> struct A<int> {
	using T = int;
	static void print (T a) { std::cout << "int" << std::endl; }
};

template<> void A<double>::print (double a) { std::cout << "double" << std::endl; }

int main( ) {
	A<char>::print('1');
	A<int>::print('1');
	A<double>::print('1');

}
#endif


