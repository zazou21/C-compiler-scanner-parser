#ifndef LEXICALANALYSIS_H
#define LEXICALANALYSIS_H

#include <string>
#include <regex>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

class LexicalAnalysis
{
public:
    class Token
    {
    public:
        std::string type;
        std::string name;
        std::string value;

        Token(const std::string &name = "", std::string value = "0", const std::string &type = "") : type(type), name(name), value(value) {}
    };

    std::vector<Token> getTokens(std::string input);
    void addToTable(Token &token);

    void printSymbolTable()
    {
        for (const auto &pair : symbolTable)
        {
            std::cout << "Key: " << pair.first << ", Value: " << pair.second.value << std::endl;
        }
    }

    static std::map<std::string, Token> symbolTable;

    std::vector<std::pair<std::string, std::string>> patterns = {
        {"COMMENT", std::string("/\\*([^*]|(\\*+[^*/]))*\\*+/|//.*$")},
        {"WHITE SPACE", std::string("[ \\n\\t]+")},
        {"TYPE_SPECIFIER", std::string("(void|char|short|int|long|float|double|signed|unsigned)")},
        {"KEYWORD", std::string("(static_assert|thread_local|sizeof|typedef|volatile|continue|register|else|default|switch|extern|static|struct|enum|const|if|goto|auto|bool|extern|false|true|inline|nullptr|restrict|typeof|typeof_unqual|union|for|while)")},
        {"BASE16", std::string("(\\+|-)?0(x|X)[0-9a-fA-F]+")},
        {"BINARY", std::string("(\\+|-)?0(b|B)[0-1]+")},
        {"BASE10 INTEGER", std::string("((\\+-)*\\+?|(-\\+)*-?)(0|[1-9][0-9]*)")},
        {"BASE8", std::string("(\\+|-)?0[0-7]*")},
        {"FLOATING NUMBER", std::string("((\\+-)*\\+?|(-\\+)*-?)(0|[1-9][0-9]*) ((e|E)(\\+|-)?[0-9]+)?")},
        {"IDENTIFIER", std::string("[a-zA-Z_][a-zA-Z0-9_]*")},
        {"SEMICOLON", std::string(";")},
        {"BRACKETS", std::string("\\(|\\)|\\[|\\]")},
        {"STRING_LITERAL", std::string("\"(\\\\.|[^\"])*\"")},
        {"CHARACTER_LITERAL", std::string("'(\\\\.|[^'])'")},
        {"Increment",std::string("\\+\\+")},
        {"Decrement",std::string("--")},
        {"Plus", std::string("\\+")},
        {"Minus", std::string("-")},
        {"Multiplication", std::string("\\*")},
        {"Division", std::string("/")},
        {"Modulo", std::string("%")},
        {"Equal to", std::string("==")},
        {"Assignment", std::string("=")},
        {"Not equal to", std::string("!=")},
        {"Greater than", std::string(">")},
        {"Less than", std::string("<")},
        {"Greater than or equal to", std::string(">=")},
        {"Less than or equal to", std::string("<=")},
        {"Logical AND", std::string("&&")},
        {"Logical OR", std::string("\\|\\|")},
        {"Logical NOT", std::string("!")},
        {"Ternary operator", std::string("\\?")},
        {"Colon", std::string(":")},
        {"Bitwise AND", std::string("&")},
        {"Bitwise OR", std::string("\\|")},
        {"Bitwise XOR", std::string("\\^")},
        {"Bitwise NOT", std::string("~")},
        {"Left shift", std::string("<<")},
        {"Right shift", std::string(">>")},
        {"Addition assignment", std::string("\\+=")},
        {"Subtraction assignment", std::string("-=")},
        {"Multiplication assignment", std::string("\\*=")},
        {"Division assignment", std::string("/=")},
        {"Modulo assignment", std::string("%=")},
        {"Left shift assignment", std::string("<<=")},
        {"Right shift assignment", std::string(">>=")},
        {"Bitwise AND assignment", std::string("&=")},
        {"Bitwise OR assignment", std::string("\\|=")},
        {"Bitwise XOR assignment", std::string("\\^=")},
        {"Opening curly brace", std::string("\\{")},
        {"Closing curly brace", std::string("\\}")},
        {"Opening square bracket", std::string("\\[")},
        {"Closing square bracket", std::string("\\]")},
        {"Opening parenthesis", std::string("\\(")},
        {"Closing parenthesis", std::string("\\)")},
        {"Semicolon", std::string(";")},
        {"Comma", std::string(",")},
        {"Dot", std::string("\\.")},
        {"Pointer access", std::string("->")},
        {"Invalid token", std::string(".")}};
};

#endif
