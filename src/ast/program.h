#pragma once
#include "src/ast/node.h"
#include <list>
#include <memory>


namespace pi {
    namespace ast {
        class Program : public Statement {
        public:
            Program() : Statement(NODE_PROGRAM) {};
            ~Program() {};

            virtual void show() override {
                printf("type: %s\n", name().c_str());
                for (auto& stmt : m_statements) {
                    printf("statement: \n");
                    stmt->show();
                }
            }
        public:
            std::list<std::shared_ptr<Statement>> m_statements;
        };
    }
}