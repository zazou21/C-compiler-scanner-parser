#include "Parser.h"
#include "parseTreeNode.h"

LexicalAnalysis lexer;

static std::map<std::string, LexicalAnalysis::Token> symbolTable;

void addToTable(LexicalAnalysis::Token &token)
{
    symbolTable.insert(std::make_pair(token.name, token));
}

void printSymbolTable()
{
    for (const auto &pair : symbolTable)
    {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second.value << std::endl;
    }
}

Parser::Parser(vector<LexicalAnalysis::Token> &tokens)
{
    buffer = tokens;
    currentToken = getNextToken();
    tree = new parseTreeNode("Program", false);
}

bool Parser::isOperator(const string &tokenType)
{
    // List of operator token types
    vector<string> operators = {
        "Increment", "Decrement", "Plus", "Minus", "Multiplication", "Division", "Modulo",
        "Equal to", "Assignment", "Not equal to", "Greater than", "Less than",
        "Greater than or equal to", "Less than or equal to", "Logical AND",
        "Logical OR", "Logical NOT", "Ternary operator", "Colon", "Bitwise AND",
        "Bitwise OR", "Bitwise XOR", "Bitwise NOT", "Left shift", "Right shift",
        "Addition assignment", "Subtraction assignment", "Multiplication assignment",
        "Division assignment", "Modulo assignment", "Left shift assignment",
        "Right shift assignment", "Bitwise AND assignment", "Bitwise OR assignment",
        "Bitwise XOR assignment"};

    // Check if the token type is in the list of operators
    return find(operators.begin(), operators.end(), tokenType) != operators.end();
}

LexicalAnalysis::Token Parser::getNextToken()
{
    if (!buffer.empty())
    {
        LexicalAnalysis::Token nextToken = buffer.front();
        buffer.erase(buffer.begin());
        return nextToken;
    }
    else
    {
        cout << "No more tokens to parse" << endl;

        return LexicalAnalysis::Token();
    }
}
bool Parser::match(LexicalAnalysis::Token expectedType)
{
    

    if (currentToken.type == "IDENTIFIER")
    {
        if (currentToken.type == expectedType.type)
        {
            currentToken = getNextToken();
            return true;
        }
        else
        {
            error="Error near "+currentToken.name+" expected "+expectedType.name;
            // cout << "Error: Expected " << expectedType.name << " but got " << currentToken.name << endl;
            return false;
        }
    }
    else if (currentToken.type == "KEYWORD")
    {
        if (currentToken.name == expectedType.name)

        {

            currentToken = getNextToken();
            return true;
        }
        else
        {
            // cout << "Error: Expected " << expectedType.name << " but got " << currentToken.name << endl;
            error="Error near "+currentToken.name+" expected "+expectedType.name;
            return false;
        }
    }
    else if (currentToken.type == "TYPE_SPECIFIER")
    {
        if (currentToken.type == expectedType.type)
        {
            currentToken = getNextToken();
            return true;
        }
        else
        {
            error="Error near "+currentToken.name+" expected "+expectedType.name;
            return false;
        }
    }

    else if (currentToken.type == "BASE10 INTEGER")
    {
        if (currentToken.type == expectedType.type)
        {
            currentToken = getNextToken();
            return true;
        }
        else{
            error="Error near "+currentToken.name+" expected "+expectedType.name;
            return false;
        }
            
    }
    else if (currentToken.type == "Multiplication")
    {
        if (currentToken.type == expectedType.type)
        {
            currentToken = getNextToken();
            return true;
        }
        else
            {
                error="Error near "+currentToken.name+" expected "+expectedType.name;
                return false;
            }
    }

    else if (currentToken.type == "SEMICOLON")
    {
        if (currentToken.type == expectedType.type)
        {
            currentToken = getNextToken();
            return true;
        }
        else{
            error="Error near "+currentToken.name+" expected "+expectedType.name;
            return false;
        
        }
    }
    else if (currentToken.type == "Comma")
    {
        if (currentToken.type == expectedType.type)
        {
            currentToken = getNextToken();
            return true;
        }
        else
            {
                error="Error near "+currentToken.name+" expected "+expectedType.name;
                return false;
            }
    }
    else
    {
        if (currentToken.type == expectedType.type)
        {
            currentToken = getNextToken();
            return true;
        }
        else
        {
            // cout << "Error: Expected " << expectedType.name << " but got " << currentToken.name << endl;
            error="Error near "+currentToken.name+" expected "+expectedType.name;
            return false;
        }
    }
}

parseTreeNode *Parser::parse_while_statement()
{
    parseTreeNode *current_node = new parseTreeNode("while-statement", false);

    // Parse "while" keyword
    // tree = current_node;

    if (match(LexicalAnalysis::Token("while", "", "KEYWORD")))
        current_node->children.push_back(new parseTreeNode("while", true));
    else
        return nullptr;

    // Parse opening parenthesis
    if (match(LexicalAnalysis::Token("(", "", "BRACKETS")))
        current_node->children.push_back(new parseTreeNode("(", true));
    else
        return nullptr;

    // Parse expression
    parseTreeNode *expression_node = parse_boolean_expression();
    if (expression_node)
        current_node->children.push_back(expression_node);
    else
        return nullptr;

    // Parse closing parenthesis
    if (match(LexicalAnalysis::Token(")", "", "BRACKETS")))
        current_node->children.push_back(new parseTreeNode(")", true));
    else
        return nullptr;

    // Parse statement
    /* parseTreeNode* statement_node = statement_with_lookahead();
     if (statement_node) current_node->children.push_back(statement_node);
     else return nullptr;*/

    if (match(LexicalAnalysis::Token("{", "", "Opening curly brace")))
    {
        current_node->children.push_back(new parseTreeNode("{", true));
    }
    else
    {
        return nullptr;
    }

    parseTreeNode *whileBlock = new parseTreeNode("block", false);

    parseTreeNode *parsedWhile = parseBlock();
    whileBlock->children.push_back(parsedWhile);
    current_node->children.push_back(whileBlock);
    while (currentToken.name != "}")
    {
        parsedWhile = parseBlock();
        whileBlock->children.push_back(parsedWhile);
    }

    if (match(LexicalAnalysis::Token("}", "", "Closing curly brace")))
    {
        current_node->children.push_back(new parseTreeNode("}", true));
    }
    else
    {
        return nullptr;
    }

    return current_node;
}
parseTreeNode *Parser::parse_boolean_expression()
{
   
    LexicalAnalysis::Token temp = currentToken;

    /* if (match(LexicalAnalysis::Token(" ", " ", "BASE10 INTEGER"))) {
         parseTreeNode* expression = new parseTreeNode("Expression", false);
         expression->children.push_back(parseTreeNode(temp.name, true));
         return expression;
     }*/

    if (buffer.size() >= 3)
    {
        if (currentToken.type == "IDENTIFIER" && isOperator(buffer[0].type))
        {
            if (symbolTable.count(currentToken.name) <= 0)
            {
                cout << currentToken.name << " is undefined";
                return NULL;
            }
        }
        if ((buffer[1].type == "IDENTIFIER" || buffer[1].type == "BASE10 INTEGER" || buffer[1].type == "STRING_LITERAL") && (buffer[2].type == "BRACKETS"))
        {
            if (buffer[1].type == "IDENTIFIER")
            {

                if (symbolTable.count(buffer[1].name) <= 0)
                {
                    cout << buffer[1].name << " is undefined";
                    return NULL;
                }
            }
            parseTreeNode *expression = new parseTreeNode("Expression", false);
            expression->children.push_back(new parseTreeNode(currentToken.name, true));
            currentToken = getNextToken();
            expression->children.push_back(new parseTreeNode(currentToken.name, true));
            currentToken = getNextToken();
            expression->children.push_back(new parseTreeNode(currentToken.name, true));
            currentToken = getNextToken();

            return expression;
        }
        else if ((buffer[1].type == "IDENTIFIER" || buffer[1].type == "BASE10 INTEGER" || buffer[1].type == "STRING_LITERAL") && (isOperator(buffer[2].type)) && (buffer[3].type == "IDENTIFIER" || buffer[3].type == "BASE10 INTEGER" || buffer[3].type == "STRING_LITERAL"))
        {
            if (buffer[1].type == "IDENTIFIER")
            {

                if (symbolTable.count(buffer[1].name) <= 0)
                {
                    cout << buffer[1].name << " is undefined";
                    return NULL;
                }
            }

            parseTreeNode *expression = new parseTreeNode("Expression", false);
            expression->children.push_back(new parseTreeNode(currentToken.name, true));
            currentToken = getNextToken();
            expression->children.push_back(new parseTreeNode(currentToken.name, true));
            currentToken = getNextToken();
            expression->children.push_back(new parseTreeNode(currentToken.name, true));
            currentToken = getNextToken();
            expression->children.push_back(new parseTreeNode(currentToken.name, true));
            currentToken = getNextToken();
            expression->children.push_back(new parseTreeNode(currentToken.name, true));
            currentToken = getNextToken();

            return expression;
        }
    }

    cout << "Error: Invalid expression syntax near: " << currentToken.name << endl;
    return NULL;
}

parseTreeNode *Parser::parseBlock()
{
    // parseTreeNode *block = new parseTreeNode("Block", false);
    // block->children.push_back(parseTreeNode(currentToken.name, true));
    // currentToken = getNextToken();
    // while (currentToken.type != "Closing curly brace")
    // {
    //     block->children.push_back(parseTreeNode(currentToken.name, true));
    //     currentToken = getNextToken();
    // }
    // return block;

    if (buffer.empty())
    {
        return nullptr;
    }

    if (currentToken.name == "if")
    {
        parseTreeNode *ifNode = parseIFCondition();
        return ifNode;
    }
    else if (currentToken.name == "while")
    {
        parseTreeNode *whileNode = parse_while_statement();
        return whileNode;
    }
    else if (currentToken.type == "TYPE_SPECIFIER")
    {
        parseTreeNode *declarationNode = declaration();
        if(declarationNode==NULL){
            return nullptr;
        }
        return declarationNode;
    }
    else if (currentToken.type == "IDENTIFIER")
    {
        parseTreeNode *assignNode = assign();
        return assignNode;
    }

    else
    {
        // cout << "Error: Invalid block syntax near: " << currentToken.name << endl;
        error="Error: Invalid block syntax near: " + currentToken.name;
        return nullptr;
    }
    return nullptr;
}

parseTreeNode *Parser::parseIFCondition()
{

    parseTreeNode *node = new parseTreeNode("If Statement", false);
    // tree = node;
    if (match(LexicalAnalysis::Token("if", "", "KEYWORD")))
    {
        node->children.push_back(new parseTreeNode("if", true));
    }
    else
    {
        return nullptr;
    }

    if (match(LexicalAnalysis::Token("(", "", "BRACKETS")))
    {
        node->children.push_back(new parseTreeNode("( ", true));
    }
    else
    {
        return nullptr;
    }

 

    parseTreeNode *expression = parse_boolean_expression();
    node->children.push_back(expression);

   
    if (match(LexicalAnalysis::Token(")", "", "BRACKETS")))
    {
        node->children.push_back(new parseTreeNode(") ", true));
    }
    else
    {
        return nullptr;
    }

    if (match(LexicalAnalysis::Token("{", "", "Opening curly brace")))
    {
        node->children.push_back(new parseTreeNode("{ ", true));
    }
    else
    {
        return nullptr;
    }
    parseTreeNode *ifBlock = new parseTreeNode("block", false);

    parseTreeNode *parsedBlock = parseBlock();
    ifBlock->children.push_back(parsedBlock);
    node->children.push_back(ifBlock);
    while (currentToken.name != "}")
    {
        parsedBlock = parseBlock();
        ifBlock->children.push_back(parsedBlock);
    }

    if (match(LexicalAnalysis::Token("}", "", "Closing curly brace")))
    {
        node->children.push_back(new parseTreeNode("}", true));
    }
    else
    {
        return nullptr;
    }

    // checking for else is not mandatory, mmkn n skip

    if (currentToken.name == "else") // look ahead abl ma a match
    {
        parseTreeNode *elseNode = new parseTreeNode("else", true);

        if (match(LexicalAnalysis::Token("else", "", "KEYWORD")))
        {

            node->children.push_back(elseNode);
            // elseNode->children.push_back(new parseTreeNode("else ", true));
        }
        else
        {
            return nullptr;
        }
        if (match(LexicalAnalysis::Token("{", "", "Opening curly brace")))
        {
            node->children.push_back(new parseTreeNode("{ ", true));
        }
        else
        {
            return nullptr;
        }

        parseTreeNode *elseblock = new parseTreeNode("block", false);
        parseTreeNode *parsedBlock = parseBlock();

        elseblock->children.push_back(parsedBlock);
        node->children.push_back(elseblock);
        while (currentToken.name != "}")
        {
            parsedBlock = parseBlock();
            elseblock->children.push_back(parsedBlock);
        }

        if (match(LexicalAnalysis::Token("}", "", "Closing curly brace")))
        {
            node->children.push_back(new parseTreeNode("} ", true));
        }
        else
        {
            return nullptr;
        }
    }

    return node;
}

parseTreeNode *Parser::parseEntryPoint()
{
    // check int main() {}
    parseTreeNode *node = new parseTreeNode("Entry Point", false);

    if (match(LexicalAnalysis::Token("int", "", "TYPE_SPECIFIER")))
    {
        node->children.push_back(new parseTreeNode("int", true));
        if (match(LexicalAnalysis::Token("main", "", "IDENTIFIER")))
        {
            node->children.push_back(new parseTreeNode("main", true));
            if (match(LexicalAnalysis::Token("(", "", "BRACKETS")))
            {
                node->children.push_back(new parseTreeNode("(", true));
                if (match(LexicalAnalysis::Token(")", "", "BRACKETS")))
                {
                    node->children.push_back(new parseTreeNode(")", true));
                    if (match(LexicalAnalysis::Token("{", "", "Opening curly brace")))
                    {
                        node->children.push_back(new parseTreeNode("{", true));
                       
                        parseTreeNode *block = parseBlock();
                        if(block==NULL){
                            return nullptr;
                        }
                        node->children.push_back(block);
                        while (currentToken.name != "}")
                        {
                            block = parseBlock();
                            if(block==NULL){
                                return nullptr;
                            }
                            node->children.push_back(block);
                        }
                        if (match(LexicalAnalysis::Token("}", "", "Closing curly brace")))
                        {
                            // return block;
                            node->children.push_back(new parseTreeNode("}", true));
                            return node;
                        }else{
                            return nullptr;
                        
                        }
                    }else{
                        return nullptr;
                    }
                }else{
                    return nullptr;
                
                }
            }else{
                return nullptr;
            }
        }else{
            return nullptr;
        
        }
    }
    else
    {
        // cout << "Error: Expected entry point int main(){}" << endl;
        error="Error: Expected entry point int main(){}";
        return nullptr;
    }
}
parseTreeNode *Parser::declarator(string &name)
{
    parseTreeNode *node = new parseTreeNode("Declarator", false);
    LexicalAnalysis::Token temp = currentToken;

    if (match(LexicalAnalysis::Token("", "", "IDENTIFIER")))
    {

        if (symbolTable.count(temp.name) <= 0)
        {
            node->children.push_back(new parseTreeNode(temp.name, true));
            name = temp.name;
            addToTable(temp);
            return node;
        }
        else if (symbolTable.count(temp.name) > 0)
        {
            // cout << "Can't redefine variables";
            error="Can't redefine variables";
            return nullptr;
        }
    }

    else
    {

        // if (match(LexicalAnalysis::Token("" , "" , "Opening parenthesis")))
        // {
        //     node->children.push_back(parseTreeNode("(", true));

        //     parseTreeNode *declarator_node = declarator();

        //     if (declarator_node)
        //     {
        //         node->children.push_back(*declarator_node);

        //         if (match(LexicalAnalysis::Token("" , "", "Closing parenthesis")))
        //             node->children.push_back(parseTreeNode(")", true));
        //         else
        //             return nullptr;
        //     }
        //     else
        //         return nullptr;

        //     return node;
        // }
        LexicalAnalysis::Token *expected = new LexicalAnalysis::Token("", "", "");
        expected->type = "Multiplication";
        if (match(*expected))
        {
            node->children.push_back(new parseTreeNode("*", true));

            //	//// Parse attr_spec_seq_opt
            //	//parseTreeNode* attr_spec_seq_opt_node = attr_spec_seq_opt();
            //	//if (attr_spec_seq_opt_node)
            //	//	node->children.push_back(attr_spec_seq_opt_node);

            //	//// Parse qualifiers_opt
            //	//parseTreeNode* qualifiers_opt_node = qualifiers_opt();
            //	//if (qualifiers_opt_node)
            //	//	node->children.push_back(qualifiers_opt_node);

            //	// Parse declarator
            parseTreeNode *declarator_node = declarator(name);

            if (declarator_node)
                node->children.push_back(declarator_node);
            

            return node;
        }
        else{
            // cout<<"expected an identifier or pointer ";
            error="expected an identifier or pointer ";

            return nullptr;
        }
    }
}
parseTreeNode *Parser::declaration()
{
    parseTreeNode *node = new parseTreeNode("Declaration", false);
 
    // tree = node;
    //  stack<LexicalAnalysis::Token> reverseBuffer;

    // Parse specifiers_and_qualifiers
    // reverseBuffer.push(currentToken);
    LexicalAnalysis::Token temp = currentToken;
    if (match(LexicalAnalysis::Token("", "", "TYPE_SPECIFIER")))
        node->children.push_back(new parseTreeNode(temp.name, true));
    else
    {
        return nullptr;
    }
    // Parse declarators_and_initializers_opt
    int value = 0;
    string identifierName;

    parseTreeNode *declarators_and_initializers_opt_node = declarators_and_initializers(value, identifierName);
    if (declarators_and_initializers_opt_node)
        node->children.push_back(declarators_and_initializers_opt_node);

    // cout << identifierName << " " << value << endl;

    symbolTable[identifierName].value = to_string(value);

    // Expect a semicolon at the end of the declaration

    if (match(LexicalAnalysis::Token(";", "", "SEMICOLON")))
        node->children.push_back(new parseTreeNode(";", true));
    else
    {
        // Handle error: Expected semicolon
        // std::cout << "Error: Expected semicolon at the end of declaration" << std::endl;
        error="Error: Expected semicolon at the end of declaration";
        return nullptr;
    }

    return node;
}

parseTreeNode *Parser::declarators_and_initializers(int &value, string &name)
{
    parseTreeNode *node = new parseTreeNode("Declarators_and_Initializers", false);

    // Parse declarator

    parseTreeNode *declarator_node = declarator(name);
    if (declarator_node)
        node->children.push_back(declarator_node);
    else
    {
        // Handle error: Expected declarator
        // std::cout << "Error: Expected declarator" << std::endl;
        error="Error: Expected declarator";
        return nullptr;
    }

    // Parse initializer_opt
    LexicalAnalysis::Token *expected = new LexicalAnalysis::Token("", "", "Assignment");
    if (match(*expected))
    {
        node->children.push_back(new parseTreeNode("=", true));

        //	// Parse initializer
        parseTreeNode *initializer_node = initializer(value);
        if (initializer_node)
        {
            node->children.push_back(initializer_node);
            symbolTable[name].value = value;
        }
        else
        {
            // Handle error: Expected initializer
            // std::cout << "Error: Expected initializer" << std::endl;
            error="Error: Expected initializer";
            return nullptr;
        }
    }

    // Parse declarators_and_initializers_opt
    string comma_counter = "";
    expected->type = "Comma";

    while (match(*expected))
    {
        node->children.push_back(new parseTreeNode("," + comma_counter, true));
        comma_counter += " ";

        //	// Parse next declarator and initializer

        parseTreeNode *next_declarator_node = declarator(name);
        if (next_declarator_node)
            node->children.push_back(next_declarator_node);
        else
        {
            //		// Handle error: Expected declarator
            // std::cout << "Error: Expected declarator" << std::endl;
            error="Error: Expected declarator";
            return nullptr;
        }
    }
    //	if (match(*expected)) {
    //		node->children.push_back(new parseTreeNode(",", true));

    //		// Parse initializer_opt for the next declarator
    //		if (match(*expected)) {
    //			node->children.push_back(new parseTreeNode("=", true));

    //			parseTreeNode* next_initializer_node = initializer();
    //			if (next_initializer_node)
    //				node->children.push_back(next_initializer_node);
    //			else {
    //				// Handle error: Expected initializer
    //				std::cout << "Error: Expected initializer" << std::endl;
    //				return nullptr;
    //			}
    //		}
    //	}
    //}

    return node;
}

parseTreeNode *Parser::initializer(int &value)
{
    parseTreeNode *node = new parseTreeNode("Initializer", false);

    LexicalAnalysis::Token *expected = new LexicalAnalysis::Token();

    // Check if initializer is an expression

    parseTreeNode *expression_node = arithmetic_expression(value);
    if (expression_node)
        node->children.push_back(expression_node);
    else
    {
        // cout << "expected expression";
        error="expected expression";
    }
    // else {
    //     // Check if initializer is a initializer-list
    //     expected->type = "Opening curly brace";
    //     if (match(*expected)) {
    //         node->children.push_back(new parseTreeNode("{", true));

    //        // Parse initializer-list
    //        parseTreeNode* initializer_list_node = initializer_list();
    //        if (initializer_list_node)
    //            node->children.push_back(initializer_list_node);
    //        else {
    //            // Handle error: Expected initializer-list
    //            std::cout << "Error: Expected initializer-list" << std::endl;
    //            return nullptr;
    //        }

    //        expected->type = "Closing curly brace";
    //        if (match(*expected))
    //            node->children.push_back(new parseTreeNode("}", true));
    //        else {
    //            // Handle error: Expected '}'
    //            std::cout << "Error: Expected '}'" << std::endl;
    //            return nullptr;
    //        }
    //    }
    //    else {
    //        // Handle error: Expected '{' or expression
    //        std::cout << "Error: Expected '{' or expression" << std::endl;
    //        return nullptr;
    //    }
    //}

    return node;
}

parseTreeNode *Parser::initializer_list(int &value)
{
    parseTreeNode *node = new parseTreeNode("Initializer-List", false);

    // Parse first initializer
    parseTreeNode *first_initializer_node = initializer(value);
    if (first_initializer_node)
        node->children.push_back(first_initializer_node);
    else
    {
        // Handle error: Expected initializer
        // std::cout << "Error: Expected initializer" << std::endl;
        error="Error: Expected initializer";
        return nullptr;
    }

    // Parse optional comma-separated list of initializers
    // LexicalAnalysis::Token* expected = new LexicalAnalysis::Token("Comma");
    // while (match(*expected)) {
    //    node->children.push_back(new parseTreeNode(",", true));

    //    parseTreeNode* next_initializer_node = initializer();
    //    if (next_initializer_node)
    //        node->children.push_back(next_initializer_node);
    //    else {
    //        // Handle error: Expected initializer after comma
    //        std::cout << "Error: Expected initializer after comma" << std::endl;
    //        return nullptr;
    //    }
    //}

    return node;
}

// Unary arithmetic matcher function
// Unary arithmetic matcher function
parseTreeNode *Parser::arithmetic_expression(int &value)
{
    // Create a parse tree node for the unary arithmetic expression
    parseTreeNode *current_node = new parseTreeNode("unary-arithmetic-expr", false);
    LexicalAnalysis::Token temp = currentToken;

    // Check if the next token is a unary plus or unary minus operator
    if (match(LexicalAnalysis::Token(" ", "", "+")))
    {
        // Create a parse tree node for unary plus operator
        current_node->children.push_back(new parseTreeNode("unary-plus", true));

        // Parse the expression following the unary plus operator
        parseTreeNode *expression_node = arithmetic_expression(value);
        if (expression_node)
        {
            current_node->children.push_back(expression_node);
        }
        else
        {
            // Error handling for missing expression
            delete current_node;
            return nullptr;
        }
    }
    else if (match(LexicalAnalysis::Token("", "", "Minus")))
    {
        // Create a parse tree node for unary minus operator
        current_node->children.push_back(new parseTreeNode("unary-minus", true));

        // Parse the expression following the unary minus operator
        parseTreeNode *expression_node = arithmetic_expression(value);
        if (expression_node)
        {
            current_node->children.push_back(expression_node);
        }
        else
        {
            // Error handling for missing expression
            delete current_node;
            return nullptr;
        }
    }
    else if (match(LexicalAnalysis::Token("", "", "BASE10 INTEGER")))
    {
        // Create a parse tree node for the number
        value = stoi(temp.name);
        // cout << temp.name << "  " << temp.type << " " << value << endl;
        current_node->children.push_back(new parseTreeNode(temp.name, true));
    }
    else
    {
        // Error handling for unexpected token
        delete current_node;
        return nullptr;
    }

    return current_node;
}

// bool Parser::parseForLoop(std::vector<LexicalAnalysis::Token> &tokens)
// {
//     if (tokens.size() < 4)
//     {
//         std::cerr << "Expected more tokens to form for loop" << std::endl;
//         return false;
//     }

//     if (tokens.front().name != "for")
//     {
//         std::cerr << "expected 'for' keyword" << std::endl;
//         return false;
//     }

//     tokens.erase(tokens.begin());

//     if (tokens.empty() || tokens.front().name != "(")
//     {
//         std::cerr << " expected '('" << std::endl;
//         return false;
//     }

//     tokens.erase(tokens.begin());

//     // initialization expression
//     if (!parseDeclaration(tokens))
//     {
//         return false;
//     }

//     // if (tokens.empty() || tokens.front().type != "SEMICOLON")
//     // {
//     //     std::cerr << "Expected ';' after initialization expression" << std::endl;
//     //     return false;
//     // }
//     // tokens.erase(tokens.begin());

//     // condition expression
//     if (!parseExpression())
//     {
//         return false;
//     }

//     if (tokens.empty() || tokens.front().type != "SEMICOLON")
//     {
//         std::cerr << "Expected ';' after condition expression" << std::endl;
//         return false;
//     }
//     tokens.erase(tokens.begin());

//     // increment expression
//     if (!parseExpression())
//     {
//         return false;
//     }

//     // Check for closing parenthesis
//     if (tokens.empty() || tokens.front().name != ")")
//     {
//         cout << tokens.front().name << endl;
//         std::cerr << "')' expected after increment expression" << std::endl;
//         return false;
//     }
//     tokens.erase(tokens.begin());

//     // Parsing block
//     // if (!parseBlock(tokens))
//     // {
//     //     return false;
//     // }

//     return true;
// }
parseTreeNode *Parser::assign()
{

    parseTreeNode *node = new parseTreeNode("variable_assign", false);
    LexicalAnalysis::Token temp = currentToken;
    int value = 0;
    if (match(LexicalAnalysis::Token("", "", "IDENTIFIER")))
    {

        if (symbolTable.count(temp.name) > 0)
        {
            node->children.push_back(new parseTreeNode(temp.name, true));
        }
        else
        {
            // cout << temp.name << " not defined.";
            error=temp.name+" not defined.";
            return nullptr;
        }

        if (match(LexicalAnalysis::Token("", "", "Assignment")))
        {
            node->children.push_back(new parseTreeNode("=", true));
            temp = currentToken;
            if (match(LexicalAnalysis::Token("", "", "IDENTIFIER")))
            {
                if (symbolTable.count(temp.name) > 0)
                {
                    node->children.push_back(new parseTreeNode(temp.name, true));
                }
                else
                {
                    // cout << temp.name << " not defined.";
                    error=temp.name+" not defined.";
                    return nullptr;
                }

                if (match(LexicalAnalysis::Token("", "", "SEMICOLON")))
                {
                    node->children.push_back(new parseTreeNode(";", true));
                }
                else
                {
                    // cout << "expected a semicolon";
                    error="expected a semicolon";
                }
            }

            else if (match(LexicalAnalysis::Token("", "", "BASE10 INTEGER")))
            {
                symbolTable[temp.name].value = temp.name;
                node->children.push_back(new parseTreeNode(temp.name, true));

                if (match(LexicalAnalysis::Token("", "", "SEMICOLON")))
                {
                    node->children.push_back(new parseTreeNode(";", true));
                }
                else
                {
                    // cout << "expected a semicolon";
                    error="expected a semicolon";
                }
            }
            else
            {
                // cout << "expected expression";
                error="expected expression";
                return nullptr;
            }

            return node;
        }
        else
        {
            // cout << "expected =";
            error="expected =";
            return nullptr;
        }
    }
    else
    {

        return nullptr;
    }
}