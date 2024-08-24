#pragma once
#include "src/token/token.h"
using namespace pi::token;

namespace pi {
    namespace ast {
        class Node {
        public:
            
            enum Type {
                NODE_INTEGER=0,
                NODE_INFIX,
                NODE_EXPRESSION_STATEMENT,
                NODE_PROGRAM
            };
            Node() {}
            Node(Type type): m_type(type) {}
            virtual ~Node() {}

            Type type() const { return m_type; }
            std::string name() const;//返回节点类型名称
            virtual void show()=0;

        public:
            Type m_type;
            Token m_token;
            static std::map<Type, std::string> m_names;
        };

        class Expression :public Node {
        public:
            Expression() : Node() {}
            Expression(Type type) : Node(type) {}
            ~Expression() {}
        };

        class Statement :public Node {
        public:
            Statement() : Node() {}
            Statement(Type type) : Node(type) {}
            ~Statement() {}
        };
        
    }
}