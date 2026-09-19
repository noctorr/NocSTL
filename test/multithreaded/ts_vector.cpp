#include "../lib/Utils/threadsafe_containers.hpp"
#include <iostream>

int main(void) {
    stl::vector<int> x { 1, 2, 3 };

    int dat[3] = {1, 4, 5};

    stl::vector<int> boom(dat);

    std::cout << boom.at(0) << std::endl;
    std::cout << x.at(2) << std::endl;
    return 0;
}
