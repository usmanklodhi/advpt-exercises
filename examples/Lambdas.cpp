void fcn1()
{
	size_t v1 = 42;  // local variable
					 // copies v1 into the callable object named f
	auto f = [v1] { return v1; };
	v1 = 0;
	auto j = f(); // j is 42; f stored a copy of v1 when we created it
	cout << j << endl;
}

void fcn2()
{
	size_t v1 = 42;  // local variable
					 // the object f2 contains a reference to v1 
	auto f2 = [&v1] { return v1; };
	v1 = 0;
	auto j = f2(); // j is 0; f2 refers to v1; it doesn't store it
	cout << j << endl;
}

void fcn3()
{
	size_t v1 = 42;  // local variable
					 // f can change the value of the variables it captures
	auto f = [v1]() mutable { return ++v1; };
	v1 = 0;
	auto j = f(); // j is 43
	cout << j << endl;
}

void fcn4()
{
	size_t v1 = 42;  // local variable
					 // v1 is a reference to a nonconst variable
					 // we can change that variable through the reference inside f2
	auto f2 = [&v1] { return ++v1; };
	v1 = 0;
	auto j = f2(); // j is 1
	cout << j << endl;
}

void fcn5()
{
	size_t v1 = 42;
	// p is a const pointer to v1
	size_t* const p = &v1;
	// increments v1, the objet to which p points
	auto f = [p]() { return ++*p; };
	auto j = f();  // returns incremented value of *p
	cout << v1 << " " << j << endl; // prints 43 43
	v1 = 0;
	j = f();       // returns incremented value of *p
	cout << v1 << " " << j << endl; // prints 1 1
}
