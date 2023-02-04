//
// Created by henry on 2/3/23.
//

#ifndef HES_HARDWARECOMPONENT_H
#define HES_HARDWARECOMPONENT_H

#include <thread>

#include <hagame/utils/loopingThread.h>
#include <iostream>

namespace hes {
class HardwareComponent : public hg::utils::LoopingThread {
    public:

        void tick() {
            m_readyToTick.store(true);
        }

    protected:

        virtual void onHardwareTick() {}

        void onTick() override {
            if (m_readyToTick) {
                onHardwareTick();
                m_readyToTick.store(false);
            }
        }

    private:

        std::atomic_bool m_readyToTick;

    };
}

#endif //HES_HARDWARECOMPONENT_H
