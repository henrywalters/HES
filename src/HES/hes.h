//
// Created by henry on 2/3/23.
//

#ifndef HES_HES_H
#define HES_HES_H

#include <thread>
#include <hagame/utils/loopingThread.h>
#include <hagame/utils/timer.h>

#include "chips/6502.h"

#include "clock.h"

namespace hes {
    class HES : public utils::LoopingThread {
    public:

        HG_GET(Clock, mainClock);
        HG_GET(long long, cycleTime);

    protected:

        void onStart() {
            m_components.push_back(std::make_unique<Chip6502>());

            for (const auto& component : m_components) {
                component->run();
            }

            m_mainClock.onTick.subscribe([&](auto tick) {
                for (const auto& component : m_components) {
                    component->tick();
                }
            });
        }

        void onTick() {
            m_mainClock.update();
            m_cycleTime = m_timer.elapsed();
            m_timer.reset();
        }

    private:

        Clock m_mainClock;

        hg::utils::Timer m_timer;
        long long m_cycleTime;

        std::vector<std::unique_ptr<HardwareComponent>> m_components;
    };
}

#endif //HES_HES_H
