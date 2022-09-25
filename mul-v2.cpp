#include <string>
#include <iostream>
#include <utility>

bool is_digit(std::string const& s) {
    if (s.length() == 0) return false;
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
    else return is_digit(s);
}

template<typename Int>
class Number {
private:
    // Description: a * 10^n

    Int a;  // 'xdd' regard as x.dd
    Int n;

public:
    static std::pair<Number, bool> from_str(std::string const& s) {
        auto e_pos = s.find_first_of("eE");
        auto decimal_part = s.substr(0, e_pos);

        Int n = 0;
        if (e_pos != std::string::npos) {
            auto exponent_part = s.substr(e_pos + 1);
            if (is_integer(exponent_part)) {
                n = std::stoll(exponent_part);
            } else {
                return {{"0.0", 0}, false};
            }
        }

        auto dot_pos = decimal_part.find('.');
        if (dot_pos != std::string::npos) {
            auto a = decimal_part.substr(0, dot_pos);
            auto b = decimal_part.substr(dot_pos + 1);
            if (is_integer(a)) {
                if (b.length() == 0) {
                    return {{a + ".0", n}, true};
                } else if (is_digit(b)) {
                    return {{decimal_part, n}, true};
                } else {
                    return {{a + ".0", n}, false};
                }
            } else {
                return {{"0.0", n}, false};
            }
        } else if (is_integer(decimal_part)) {
            return {{decimal_part + ".0", n}, true};
        } else {
            return {{"0.0", n}, false};
        }
    }

    // a * 10^n
    Number(std::string const& a_, Int n_) {
        auto dot_pos = a_.find('.');
        auto s = a_.substr(0, dot_pos) + a_.substr(dot_pos + 1);
	while (!s.empty() && s.back() == '0') { s.pop_back(); }
        auto non_zero_pos = s.find_first_not_of('0');
        if (non_zero_pos != std::string::npos) {
            auto t = dot_pos - non_zero_pos - 1;
            this->a = std::stoll(s);
            this->n = n_ + t;
        } else {
            this->a = 0;
            this->n = 0;
        }
    }

    Number operator*(Number const& other) const {
        auto l1 = std::to_string(std::abs(this->a)).length() - 1;
        auto l2 = std::to_string(std::abs(other.a)).length() - 1;
        auto p = std::to_string(this->a * other.a);
        auto t = l1 + l2;
        if (p == "0") {
            return { "0.0", 0 };
        } else {
            return {
                p.insert(p.length() - t, "."),
                this->n + other.n,
            };
        }
    }

    std::string to_str() const {
        auto s = std::to_string(a);
        return s.insert(s.find_first_not_of("+-") + 1, ".") + ((n == 0) ? "" : ("e" + std::to_string(n)));
    }
};

template<typename Int>
std::string to_string(Number<Int> const& num) {
    return num.to_str();
}

template<typename Int>
std::ostream& operator<<(std::ostream& os, Number<Int> const& num) {
    os << num.to_str();
    return os;
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

    using Num = Number<long long int>;

    auto [n1, f1] = Num::from_str(s[0]);
    auto [n2, f2] = Num::from_str(s[1]);

    Num num[2] = { n1, n2 };

    bool parse_succeeded = f1 && f2;

    if (!parse_succeeded) {
        std::cout << "Program terminated.\n";
        return 1;
    }

    auto result = num[0] * num[1];
    
    std::cout << num[0] << " * " << num[1] << " = " << result << "\n";

    return 0;
}
