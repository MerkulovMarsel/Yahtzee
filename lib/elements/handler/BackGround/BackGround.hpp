//
// Created by Марсель on 21.08.2025.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "UIManger/PositionManger/PositionManager.hpp"
#include "UIManger/UIManager.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "elements/base/general/StaticUntouchable/StaticUntouchableElement.hpp"
#include "UIManger/ElementsTypes/ElementsTypes.h"
#include "elements/handler/Tracker.hpp"

namespace elements {
    template<Page page>
    class BackGround final : public PageElement<page>,
                             public StaticUntouchableElement,
                             UITracker {
    public:
        explicit BackGround(const UIManager& manager) :
            StaticUntouchableElement(
        { .texture = manager.texture_manager.get_background_texture(page),
            .position = PositionManager::get_background_position()}),
            UITracker(manager) {
        }
    };

    using StartSettingsBackGround   = BackGround<Page::START_SETTING>;
    using ConfigSettingsBackGround  = BackGround<Page::CONFIG_SETTINGS>;
    using GameBackGround            = BackGround<Page::GAME_PLAYING>;
    using GameOverBackGround        = BackGround<Page::GAME_OVER>;
}

#endif //BACKGROUND_H
