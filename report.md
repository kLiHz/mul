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

如果不满足被解释为整数的条件, 再尝试解析为浮点数.

解析浮点数的思路是分为两种情况处理, 一种是包含字符 `e`, 一种是不包含字符 `e`;

- 包含字符 `e` 的情况是分为前后两半, 前半部分应为一个合法的小数, 使用 `is_decimal` 函数判断, 后者应为一个合法的整数, 使用 `is_integer` 判断;
- 不包含字符 `e` 的情况, 则整个部分应该为一个合法的小数, 使用 `is_decimal` 函数判断.

```cpp
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
```

## 计算结果

现有的实现中, 采用了两个 `long long` 型变量和两个 `double` 型变量来存储解析的结果.

由于两数可能不同属于一个类型, 继而存储在不同的变量数组中, 因此需要在运算时根据 `is_int` 数组中存储的信息进行判断, 选择正确的变量进行运算.

为了简便, 使用 `double` 类型作为运算中间变量的类型.

```cpp
double foo(bool is_int[], long long ll_value[], double double_value[]) {
    double result = 1;
    for (int i = 0; i < 2; ++i) {
        if (is_int[i]) {
            result = result * (double) ll_value[i];
        } else {
            result = result * double_value[i];
        }
    }
    return result;
}
```
