#include "node.h"
using namespace pi::ast;
std::map<Node::Type, std::string> Node::m_names = {
    {Node::Type::NODE_INTEGER,              "integer"},
    {Node::Type::NODE_INFIX,                "infix"},
    {Node::Type::NODE_EXPRESSION_STATEMENT, "expression_statement"},
    {Node::Type::NODE_PROGRAM,              "program"}
};

std::string Node::name() const {
    auto it = m_names.find(m_type);
    if (it != m_names.end()) {
        return it->second;
    }
    return "";
}
