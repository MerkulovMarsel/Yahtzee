//
// Created by Марсель on 21.08.2025.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "element/base/StaticUntouchable/StaticUntouchableElement.h"
#include "element/handler/Tracker.h"

namespace elements {
    template<Page page>
    class BackGround final : public StaticUntouchableElement<page>, UITracker {
    public:
        explicit BackGround(const UIManager& manager) :
            StaticUntouchableElement<page>(
        *manager.texture_manager.get_background_texture(page),
        PositionManager::get_background_position()),
            UITracker(manager) {
        }
    };

    using StartSettingsBackGround   = BackGround<Page::START_SETTING>;
    using ConfigSettingsBackGround  = BackGround<Page::CONFIG_SETTINGS>;
    using GameBackGround            = BackGround<Page::GAME_PLAYING>;
    using GameOverBackGround        = BackGround<Page::GAME_OVER>;
}

#endif //BACKGROUND_H
