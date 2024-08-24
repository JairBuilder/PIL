#pragma once
#include "src/ast/node.h"
#include <memory>

namespace pi {
    namespace ast {
        class Infix : public Expression {
        public:
            Infix() : Expression(NODE_INFIX) {};
            ~Infix() {};

            virtual void show() override {
                printf("type: %s \toperator: %s\n", name().c_str(), m_operator.c_str());
                printf("left:\n");
                m_left->show();
                printf("right:\n");
                m_right->show();
            }
        public:
            std::string m_operator;
            std::shared_ptr<Expression> m_left;
            std::shared_ptr<Expression> m_right;
        };
    }
}