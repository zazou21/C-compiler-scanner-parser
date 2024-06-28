#include "LexicalAnalysis.h"
#include <fstream>
#include <vector>

std::map<std::string, LexicalAnalysis::Token> LexicalAnalysis::symbolTable;
void LexicalAnalysis::addToTable(LexicalAnalysis::Token &token)
{
    symbolTable.insert(std::make_pair(token.name, token));
}

std::vector<LexicalAnalysis::Token> LexicalAnalysis::getTokens(std::string input)
{
    std::string reg;
    for (auto const &x : patterns)
        reg += "(" + x.second + ")|";

    reg.pop_back();

    std::regex re(reg);

    std::sregex_iterator iter(input.begin(), input.end(), re);
    std::sregex_iterator end;
    std::vector<Token> tokens;
    for (auto it = iter; it != end; ++it)
    {
        for (auto pattern : patterns)
        {
            if (std::regex_match(it->str(), std::regex(pattern.second)))
            {
                if (pattern.first == "WHITE SPACE")
                    break;

                Token *token = new Token();
                token->name = it->str();
                token->type = pattern.first;
                tokens.push_back(*token);

                // std::cout << it->str() << "\t" << pattern.first << std::endl;
                break;
            }
        }
    }
    return tokens;
}

/*for (auto it = iter; it != end; ++it) {
    for (auto pattern : patterns) {
        if (std::regex_match(it->str(), std::regex(pattern.second))) {
            if (pattern.first == "WHITE SPACE")
                break;
            if (pattern.first == "IDENTIFIER") {
                Token* token = new Token(it->str());
                token->type = "IDENTIFIER";
                if (it != end) {
                    std::sregex_iterator next = it;
                    ++next;
                    if (next != end && std::regex_match(next->str(), std::regex("[ \\n\\t]+"))) {
                        ++next;
                        while (next != end && std::regex_match(next->str(), std::regex("[ \\n\\t]+"))) {
                            ++next;
                        }
                        if (next != end && std::regex_match(next->str(), std::regex("\\="))) {
                            ++next;
                            while (next != end && std::regex_match(next->str(), std::regex("[ \\n\\t]+"))) {
                                ++next;
                            }
                            if (next != end) {
                                token->value = next->str();
                                LexicalAnalysis::addToTable(*token);
                                tokens.push_back(*token);
                            }
                        }

                    }
                }
            }
            else {
                Token* token = new Token();
                token->name = it->str();
                token->type = pattern.first;
                tokens.push_back(*token);
            }
            std::cout << it->str() << "\t" << pattern.first << std::endl;
            break;
        }
    }
}
return tokens;

}*/
/* if (!std::isspace(input[position + length])) {


     length++;
 }
 else {
     std::string substr = input.substr(position, length);
     for (const auto& pair : patterns) {
         const std::string& type = pair.first;
         const std::regex& pattern = pair.second;
         a
         if (std::regex_search(substr, match, pattern)) {
             std::cout << "<" << type << "> " << match.str() << std::endl;



             break;
         }

     }
     position = position + length + 1;
     length = 0;



*/

void read_file(std::string filepath, std::string &buffer)
{
    std::ifstream file(filepath);
    std::string line;
    while (getline(file, line))
    {
        buffer.push_back('\n');
        buffer += line;
    }
    file.close();
}

//}
