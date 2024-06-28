#include <string>
#include <iostream>
#include <cstdlib>
#include "LexicalAnalysis.h"
#include <deque>
#include <vector>
#include "parseTreeNode.h"
using namespace std;

class Parser
{
public:
	vector<LexicalAnalysis::Token> buffer;
	LexicalAnalysis::Token currentToken;
	parseTreeNode *tree;
	string error;

	Parser(vector<LexicalAnalysis::Token> &tokens);
	LexicalAnalysis::Token getNextToken();
	bool match(LexicalAnalysis::Token token);
	bool isOperator(const string &tokenType);

	parseTreeNode *declaration();
	parseTreeNode *declarators_and_initializers(int &value, string &name);
	parseTreeNode *declarator(string &name);
	parseTreeNode *initializer(int &value);
	parseTreeNode *initializer_list(int &value);
	parseTreeNode *arithmetic_expression(int &value);
	parseTreeNode *parse_while_statement();
	parseTreeNode *parseIFCondition();
	parseTreeNode *parse_boolean_expression();
	parseTreeNode *parseBlock();
	parseTreeNode *parseEntryPoint();
	parseTreeNode *assign();

	// bool parseForLoop(std::vector<LexicalAnalysis::Token> &tokens);
};