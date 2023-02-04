//
// Created by henry on 1/29/23.
//

#ifndef HAGAMELITEEDITOR_EDITOR_H
#define HAGAMELITEEDITOR_EDITOR_H

#include <iostream>
#include <thread>

#include "hagame/core/scene.h"
#include "hagame/graphics/primitives/quad.h"
#include "hagame/utils/random.h"
#include "hagame/graphics/renderPasses.h"

#include "../components/renderable.h"
#include "../assets.h"
#include "../standardRenderer.h"

#include "../HES/hes.h"

namespace hg {

    class HESDebug : public hg::Scene {
    public:

        void onInit() override {
            utils::Random rand;
            m_hes = std::make_unique<hes::HES>();
            m_hes->run();
        }

        void onUpdate(double dt) override {

            ImGui::Begin("HES");

            ImGui::Text(("Tick: " + std::to_string(m_hes->mainClock().ticks() % 1000000000)).c_str());
            ImGui::Text(("Cycle Time: " + std::to_string(m_hes->mainClock().delta()) + " nanoseconds").c_str());

            ImGui::End();

        }

        void onDeactivate() override {
            m_hes->stop();
        }

    private:

        std::unique_ptr<hes::HES> m_hes;
    };
}
#endif //HAGAMELITEEDITOR_EDITOR_H
