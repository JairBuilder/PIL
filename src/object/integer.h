#pragma once
#include "object.h"
using namespace pi::object;

namespace pi {
    namespace object {
        class Integer : public Object{
        public:
            Integer() : Object(OBJECT_INTEGER),m_value(0) {}
            Integer(int64_t value) : Object(OBJECT_INTEGER), m_value(value) {}
            ~Integer() {}

            int64_t value() const { return m_value; }
            virtual std::string str() const {
                return std::to_string(m_value);
            }
        public:
            int64_t m_value;
        };
    }
}