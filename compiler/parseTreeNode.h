#ifndef PARSETREENODE_H
#define PARSETREENODE_H

#include <string>
#include <deque>
#include <fstream>

class parseTreeNode
{
public:
    parseTreeNode(std::string n, bool t) : name(n), isTerminal(t) {}
    std::string name;
    bool isTerminal;
    std::deque<parseTreeNode *> children;
};

#endif // PARSETREENODE_H
