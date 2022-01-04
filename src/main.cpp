#include <iostream>
#include <string_view>

int main() {
    using namespace std::string_view_literals;
    const auto source = "const name = \"coder2k\";\n"
                        "mutable age = 34u;\n"
                        "age = age + 10u;\n"
                        "print name + \" is \" + @age + \" years old\";"sv;
    // Lexer output:
    // =============
    //
    // [const] [identifier] [equals] [string_literal] [semicolon]
    // [mutable] [identifier] [equals] [u64_literal] [semicolon]
    // [identifier] [equals] [identifier] [plus] [u64_literal] [semicolon]
    // [print] [identifier] [plus] [string_literal] [plus] [at] [identifier] [plus] [string_literal] [semicolon]
}
