#include ".../lib/Utils/threadsafe_containers.hpp"
#include <iostream>

int main(void) {
    stl::vector<int> x { 1, 2, 3 };

    std::cout << x.at(2) << std::endl;
    return 0;
}
