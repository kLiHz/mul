#include <string>
#include <iostream>

bool is_digit(std::string const& s) {
    for (auto const & c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

bool is_integer(std::string const& s) {
    auto c = s.front();
    if (c == '-' || c == '+') {
        return is_digit(s.substr(1));
    }
    return is_digit(s);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Illegal arguments.\n";
        std::cout << "Usage:\n"
                  << "    " << argv[0] << " arg1 arg2" << "\n";
        return 1;
    }

    std::string s[2] = { argv[1], argv[2] };
    std::cout << "Arguments are '" << s[0] << "' and '" << s[1] << "'\n";

    bool is_int[2];

    long long ll_value[2];
    double double_value[2];

    for (int i = 0; i < 2; ++i) {
        is_int[i] = is_integer(s[i]);
        if (is_int[i]) {
            ll_value[i] = std::stoll(s[i]);
            std::cout << "Input '" << s[i] << "' are interpreted as int: " << ll_value[i] << "\n";
        } else {
            std::cout << "The input '" << s[i] << "' cannot be interpreted as number.\n";
        }
    }

    return 0;
}
