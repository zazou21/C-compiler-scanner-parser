#include "mainwindow.h"
#include "qsvgwidget.h"
#include "ui_mainwindow.h"
#include <QSvgRenderer>
#include <QGraphicsView>
#include <QGraphicsSvgItem>
#include <QtSvg>
#include "Parser.h"
#include "LexicalAnalysis.h"
#include <iostream>
#include <vector>
#include "parseTreeNode.h"

void visualize_parse_tree_aux(parseTreeNode *node, std::ostream &out, int &counter)
{
    std::string unique_name = node->name + "_" + std::to_string(counter);
    out << "  \"" << unique_name << "\"";
    out << " [label=\"" << node->name << "\"]"; // Add original node name as label
    out << (node->isTerminal ? "[fontcolor=\"red\"][color=\"red\"];\n" : ";\n");

    for (auto &child : node->children)
    {
        bool child_has_children = !child->children.empty();
        if (child->isTerminal || (!child->isTerminal && child_has_children))
        {
            std::string child_unique_name = child->name + "_" + std::to_string(counter + 1);
            out << "  \"" << unique_name << "\" -> \"" << child_unique_name << "\";\n";
            visualize_parse_tree_aux(child, out, ++counter);
        }
    }
}

void visualize_parse_tree(parseTreeNode *root)
{
    std::ofstream dot_file_out("parse_tree.dot", std::ios::trunc);

    dot_file_out << "digraph G {\n";
    int counter = 0;
    visualize_parse_tree_aux(root, dot_file_out, counter);
    dot_file_out << "}";
    dot_file_out.close();

    system("dot -Tsvg ./parse_tree.dot -o parse_tree.svg");
    system("start parse_tree.svg");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


LexicalAnalysis lex;
string text;


void MainWindow::on_compilebtn_clicked()
{
    text = ui->textarea->toPlainText().toStdString();
    vector<LexicalAnalysis::Token> tokens = lex.getTokens(text);
    Parser parser(tokens);

    //ui->label_2->setText(QString::fromStdString(text));
    // parseTreeNode *block = parser.parseBlock();

    parseTreeNode *block = parser.parseEntryPoint();
    if(block == nullptr)
    {
        cout<<parser.error<<endl;
        ui->label_2->setText(QString::fromStdString(parser.error));
        return;
    }
    parser.tree->children.push_back(block);

    while (!parser.buffer.empty())
    {
        block = parser.parseEntryPoint();
        if(block == nullptr)
        {
            cout<<parser.error<<endl;
            ui->label_2->setText(QString::fromStdString(parser.error));
            break;
        }
        parser.tree->children.push_back(block);
    }
    visualize_parse_tree(parser.tree);
    // Create the parent widget
    QWidget* window = new QWidget;

    // Load the SVG image
    QSvgWidget* svgWidget = new QSvgWidget(QStringLiteral("/Users/Mohamed/OneDrive/Desktop/Education/Pdfs/Junior 2/Design of Compilers/Project/GUI/build-compiler-Desktop_Qt_6_6_1_MinGW_64_bit-Debug/parse_tree.svg"), window);
    svgWidget->setGeometry(50, 100, 900, 400);


    // Show the window
    window->show();
}
