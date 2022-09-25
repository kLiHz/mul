#include <string>
#include <iostream>

bool is_integer(std::string const& s) {
    auto i = s.begin();
    if (*i == '-' || *i == '+') {
        ++i;
        if (i == s.end()) return false;
    }
    for ( ; i != s.end(); ++i) {
        if (*i < '0' || *i > '9') {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Illegal arguments.\n";
        std::cout << "Usage:\n"
                  << "    " << argv[0] << " arg1 arg2" << "\n";
        return 1;
    }
    std::string a = argv[1];
    std::string b = argv[2];
    std::cout << "Arguments are '" << a << "' and '" << b << "'\n";
    std::cout << std::boolalpha;
    std::cout << "Is '" << a << "' an integer? " << is_integer(a) << "\n";
    std::cout << "Is '" << b << "' an integer? " << is_integer(a) << "\n";
    return 0;
}
