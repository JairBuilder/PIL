#pragma once
#include "src/ast/node.h"
#include <memory>

namespace pi {
    namespace ast {
        class ExpressionStatement : public Statement {
        public:
            ExpressionStatement() : Statement(NODE_EXPRESSION_STATEMENT) {};
            ~ExpressionStatement() {};

            virtual void show() override {
                printf("type: %s:\n", name().c_str());
                printf("expression:\n");
                m_expression->show();
            }

        public:
            std::shared_ptr<Expression> m_expression;
        };
    }
}