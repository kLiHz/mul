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

bool is_decimal(std::string const& s) {
    auto dot_pos = s.find('.');
    if (dot_pos != std::string::npos) {
        auto a = s.substr(0, dot_pos);
        auto b = s.substr(dot_pos + 1);
        if (b.length() == 0) {
            return is_integer(a);
        } else {
            return is_integer(a) && is_digit(b);
        }
    } else {
        return is_integer(s);
    }
}

bool is_float(std::string const& s) {
    auto e_pos = s.find_first_of("eE");
    if (e_pos != std::string::npos) {
        auto decimal_part = s.substr(0, e_pos);
        auto exponent_part = s.substr(e_pos + 1);
        return is_decimal(decimal_part) && is_integer(exponent_part);
    } else {
        return is_decimal(s);
    }
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
    bool parse_failed = false;

    long long ll_value[2] = { 0, 0 };
    double double_value[2] = { 0, 0 };

    for (int i = 0; i < 2; ++i) {
        is_int[i] = is_integer(s[i]);
        if (is_int[i]) {
            ll_value[i] = std::stoll(s[i]);
            std::cout << "Input '" << s[i] << "' are interpreted as int: " << ll_value[i] << "\n";
        } else if (is_float(s[i])) {
            double_value[i] = std::stod(s[i]);
            std::cout << "Input '" << s[i] << "' are interpreted as float: " << double_value[i] << "\n";
        } else {
            std::cout << "The input '" << s[i] << "' cannot be interpreted as number.\n";
            parse_failed = true;
        }
    }

    if (parse_failed) {
        std::cout << "Program terminated.\n";
        return 1;
    }

    double result = 1;

    for (int i = 0; i < 2; ++i) {
        if (is_int[i]) {
            result = result * (double) ll_value[i];
        } else {
            result = result * double_value[i];
        }
    }
    
    std::cout << s[0] << " * " << s[1] << " = " << result << "\n";

    return 0;
}
