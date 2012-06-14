#include "curry.h"

#include <iostream>

std::function<int(int)> get_closure(int x)
{
    auto f = curry([](int x, int y){ return x*y; });
    return f(x);
}
std::function<int(int)> get_closure()
{
    auto f = curry([](int x, int y){ return x*y; });
    return f(5);
}

int main()
{
    auto curried = curry([](int x, int y, int z) { return x+y+z; });
    std::cout << curried(1)(2)(3) << std::endl;

    auto closure = get_closure();
    std::cout << closure(3) << std::endl;

    closure = get_closure(6);
    std::cout << closure(3) << std::endl;
}
