#include <iostream>
#include <variant>
#include <string>

int main() {
    std::variant<int, double, std::string> v = "hello";
    v = 42;

    std::visit([](auto &&x) { std::cout << x << std::endl; }, v);

    v = 3.14;
    std::visit([](auto &&x) { std::cout << x << std::endl; }, v);

    return 0;
}
