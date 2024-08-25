#pragma once
#include <vector>
#include "code.h"
#include <cstdint>

namespace pi {
    namespace code {
        class Instruction {
            public:
                enum ByteOrder {
                    BigEndian=0,
                    LittleEndian,
                };
                Instruction();
                ~Instruction()=default;

                bool make(Code::Opcode op,const std::vector<int>& operands={});
                void write(uint8_t value);
                void write(uint16_t value);
                bool read(uint8_t& value);
                bool read(uint16_t& value);

                Code::Opcode opcode();
                int size() const;
                std::string str();
            public:
                std::vector<char> m_data;
                ByteOrder m_byteorder;
            private:
                ByteOrder byteorder();
                void write(const char* data, size_t len);
                bool read(char* data, size_t len);
                int m_offset=0;
        };
    }
}