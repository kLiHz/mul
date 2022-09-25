# Report: Project Mul

## 读取命令行参数

命令行选项能够从 `main` 函数的参数中读取到. 

传入的参数应为字符串形式, 存储在 `std::string` 类型中.

代码如下:

```cpp
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
```

## 解析传入的参数

合法的参数应当能够被解析为整数或浮点数.

这里规定可以被解析为整数的字符串的格式为十进制浮点数; 可以被解析为浮点数的字符串的格式为十进制, 且可能包含小数点以及 `e` 标记的 10 的幂.

示例:

- 整数: `12345`, `-12345`;
- 浮点数: `1234`, `1.234`, `1.1e5`.

由于整数字符串也能被解析为浮点数, 因此先判断字符串是否为整数.

下面定义 `is_integer` 函数, 接收一个 `std::string`,
返回值 `true` 表示该字符串可以被认为是整数,
返回值 `false` 说明不能被认为是整数.

```cpp
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
```
