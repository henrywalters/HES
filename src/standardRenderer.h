//
// Created by henry on 2/2/23.
//

#ifndef HAGAMELITEEDITOR_STANDARDRENDERER_H
#define HAGAMELITEEDITOR_STANDARDRENDERER_H

#include "hagame/graphics/renderPipeline.h"
#include "hagame/graphics/renderPasses.h"
#include "hagame/graphics/mesh.h"
#include "hagame/graphics/primitives/quad.h"

using namespace hg;
using namespace hg::graphics;
using namespace hg::math;

enum class RenderMode {
    Geometry,
    Normals,
};

class StandardRenderer : public RenderPipeline {
public:

    StandardRenderer() {
        m_renderPasses = std::make_unique<RenderPasses<RenderMode>>();
        m_renderPasses->create(RenderMode::Geometry, HD);
        m_renderPasses->create(RenderMode::Normals, HD);

    }

    void clear() override {
        m_renderPasses->clear(RenderMode::Geometry, Color::black());
    }

    void render(Vec2i _size) override {

        auto proj = Mat4::Orthographic(0, _size[0], 0, _size[1], -20, 20);
        auto view = Mat4::Identity();
        SHADERS.get("test")->setMat4("projection", proj);
        SHADERS.get("test")->setMat4("view", view);

        m_renderPasses->bind(RenderMode::Geometry);

        scene()->entities.forEach<Renderable>([&](const auto& renderable, const auto& entity) {
            renderable->shader->use();
            renderable->shader->setMat4("model", entity->transform.getModel());
            renderable->mesh->render();
        });

        m_renderPasses->render(RenderMode::Geometry);
        m_renderPasses->unbind(RenderMode::Geometry);

        m_renderPasses->activateTextures();
    }

    RawTexture<GL_RGBA>* outputTexture() override {
        return m_renderPasses->get(RenderMode::Geometry)->texture.get();
    }

private:
    std::unique_ptr<RenderPasses<RenderMode>> m_renderPasses;

};

#endif //HAGAMELITEEDITOR_STANDARDRENDERER_H
