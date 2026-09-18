#include "../lib/SIMD/GCC.hpp"

#include <iostream>

int main(void) {
    stl::FMD64 vector1 = {1.f, 2.f};
    stl::FMD64 vector2 = {4.f, 5.1f};

    stl::md::padd_fmd64(vector1, vector2);
    std::cout << "Result of padd_fmd64: " << "{ " << vector1[0] << ", " << vector1[1] << " }" << std::endl;
    return 0;
}
