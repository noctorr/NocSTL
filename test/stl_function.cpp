#include "../lib/Utils/function.hpp"
#include <iostream>

double x(int z) { return 2.0; }

int main(void) {
    stl::function<double (int)> funcObj;
    funcObj.set(x);

    double y = funcObj(1);
    
    std::cout << y;

    stl::function<double (int)> test(x);

    double z = test(1);

    std::cout << z;
    return 0;
}
