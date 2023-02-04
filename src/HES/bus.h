//
// Created by henry on 2/3/23.
//

#ifndef HES_BUS_H
#define HES_BUS_H

#include <memory>
#include <array>
#include <cstdint>

namespace hes {
    class Bus {
    public:

        Bus() {
            for (auto& i: m_ram) i = 0x00;
        }

        bool inRange(uint16_t addr) {
            return addr >= 0x000 && addr <= 0xFFFF;
        }

        void write(uint16_t addr, uint8_t data) {
            if (!inRange(addr)) {
                throw std::runtime_error("Write address out of range");
            }

            m_ram[addr] = data;
        }

        uint8_t read(uint16_t addr, bool readOnly = false) {
            if (!inRange(addr)) {
                return 0x00;
            }

            return m_ram[addr];
        }

    private:
        std::array<uint8_t, 64 * 1024> m_ram;
    };
}

#endif //HES_BUS_H
