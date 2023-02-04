//
// Created by henry on 2/3/23.
//

#ifndef HES_6502_H
#define HES_6502_H

#include "../hardwareComponent.h"

namespace hes {

    class Chip6502 : public HardwareComponent {
    public:

        enum class StatusFlags {
            C = (1 << 0),
            Z = (1 << 1),
            I = (1 << 2),
            D = (1 << 3),
            B = (1 << 4),
            U = (1 << 5),
            V = (1 << 6),
            N = (1 << 7),
        };

    protected:

        virtual void onHardwareTick() override {

        }
    private:

        uint16_t m_pc;
        uint8_t m_sp;

        uint8_t m_a;
        uint8_t m_x;
        uint8_t m_y;

        uint8_t st;
    };
}

#endif //HES_6502_H
