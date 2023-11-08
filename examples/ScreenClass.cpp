class Screen0 {

private:
	size_t size;
	int color;
	int* data;

public:

	Screen0() : data(nullptr), size(0) {
		std::cout << "std constructor" << std::endl;
	}

	Screen0(size_t size_, int color) : color(color), size(size_),
		data(new int[size]) {
		std::cout << "size,col constructor" << std::endl;
	}

	Screen0(const int& i) : size(0) {
		std::cout << "conv. constructor" << std::endl;
	}

	Screen0(const int&& i) : size(0) {
		std::cout << "conv. constructor rr" << std::endl;
	}

	Screen0(const Screen0&)
	{
		std::cout << "copy constructor" << std::endl;
	}
	Screen0 &operator=(Screen0&)
	{
		std::cout << "copy assignment" << std::endl; return *this;
	}

	Screen0(Screen0&&)
	{
		std::cout << "move constructor" << std::endl;
	}
	Screen0 &operator=(Screen0&&)
	{
		std::cout << "move assignment" << std::endl; return *this;
	}

	~Screen0() {
		std::cout << "destructor" << std::endl;
		//delete [] data;
	}

	int getsize() const { std::cout << "getsize const" << std::endl; return size; }

	void setsize(const int& size) { this->size = size; }
	int getcolor() { return color; }

	int getdata(int i) { return data[i]; }
};

