//
// Created by henry on 2/3/23.
//

#ifndef HES_CLOCK_H
#define HES_CLOCK_H

#include <hagame/utils/macros.h>
#include <hagame/utils/clock.h>

namespace hes {
    class Clock {
    public:

        long nsPerTick = 500;

        hg::EventEmitter<long> onTick;

        Clock():
            m_ticks(0),
            m_clockTicks(0),
            m_lastClock(hg::utils::Clock::Now())
        {}

        void update() {
            auto now = hg::utils::Clock::Now();
            auto offset = now - m_lastClock;
            m_clockTicks += offset;
            auto elapsedTicks = m_clockTicks / nsPerTick;

            if (elapsedTicks > 0) {
                m_ticks += elapsedTicks;
                onTick.emit(m_ticks);
                m_clockTicks = m_clockTicks % nsPerTick;
            }

            m_delta = now - m_lastClock;

            m_lastClock = now;
        }

        HG_GET(long long, ticks);
        HG_GET(long long, delta);

    private:

        long long m_ticks;

        long long m_lastClock;
        long long m_clockTicks;

        long long m_delta;
    };
}

#endif //HES_CLOCK_H
