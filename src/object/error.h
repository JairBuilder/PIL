#pragma once
#include "object.h"
using namespace pi::object;

namespace pi {
    namespace object {
        class Error : public Object{
        public:
            Error() : Object(OBJECT_ERROR),m_message("") {}
            Error(const std::string & message) : Object(OBJECT_ERROR), m_message(message) {}
            ~Error() {}

            std::string message() const { return m_message; }
            virtual std::string str() const {
                return "error: " + m_message;
            }
        public:
            std::string m_message;
        };
    }
}