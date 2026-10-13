#include <iostream>
#include <optional>
#include <string>

std::optional<int> get_value(const std::string &name) {
    if (name == "Alice") return 1;
    if (name == "Bob") return 2;
    return std::nullopt;
}

int main() {
    const char *names[] = {"Alice", "Bob", "Charlie"};
    for (auto name : names) {
        if (auto v = get_value(name)) {
            std::cout << name << " = " << *v << std::endl;
        } else {
            std::cout << name << " = no value" << std::endl;
        }
    }
    return 0;
}
