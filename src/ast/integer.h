#pragma once
#include "src/ast/node.h"

namespace pi {
    namespace ast {
        class Integer : public Expression {
        public:
            Integer() : Expression(NODE_INTEGER) {};
            ~Integer() {};

            virtual void show() override {
                printf("%s: %ld\n",name().c_str(), m_value);
            }
        public:
            int64_t m_value;
        };
    }
}