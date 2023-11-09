
#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string line;
    std::getline(std::cin, line);

    line.erase(std::remove_if(line.begin(), line.end(), ispunct), line.end());

    std::cout << line << std::endl;

    return 0;
}
