//
// Created by Марсель on 21.08.2025.
//

#ifndef PAGECHANGERBUTTON_H
#define PAGECHANGERBUTTON_H
#include "UIManger/ElementsTypes/ElementsTypes.h"
#include "UIManger/UIManager.hpp"
#include "elements/base/general/StaticTouchable/StaticTouchableElement.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "UIManger/PositionManger/PositionManager.hpp"
#include "elements/base/interfaces/element/Element.hpp"
#include "elements/handler/Tracker.hpp"

namespace elements {
    template<Page page_from, Page page_to>
    class PageChangerButton final : public PageElement<page_from>,
                                    public StaticTouchableElement<Page>,
                                    public UITracker {
    public:
        explicit PageChangerButton(UIManager& manager) :
            StaticTouchableElement<Page>(
        manager.current_page,

        { .texture = manager.texture_manager.get_change_page_button_texture(),
        .position = PositionManager::get_change_page_button_position()},

        { .touch_callback = [](Page &page, MousePos) { if (page == page_from) { page = page_to; }}}),

            UITracker(manager) {
        }
    };

    using OpenConfigSettingsFromStartSettingButton = PageChangerButton<Page::START_SETTING, Page::CONFIG_SETTINGS>;
    using BackToStartSettingsFromConfigSettingsButton = PageChangerButton<Page::CONFIG_SETTINGS, Page::START_SETTING>;
}

#endif //PAGECHANGERBUTTON_H
