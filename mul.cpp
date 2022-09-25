#include <string>
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Illegal arguments.\n";
        std::cout << "Usage:\n"
                  << "    " << argv[0] << " arg1 arg2" << "\n";
        return 1;
    }
    std::string a = argv[1];
    std::string b = argv[2];
    std::cout << "Arguments are '" << a << "' and '" << b << "'\n";
    return 0;
}
