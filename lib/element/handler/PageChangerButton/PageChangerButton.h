//
// Created by Марсель on 21.08.2025.
//

#ifndef PAGECHANGERBUTTON_H
#define PAGECHANGERBUTTON_H
#include "UIManger/PositionManger/PositionManager.h"
#include "element/base/StaticTouchable/StaticTouchableElement.h"
#include "element/handler/Tracker.h"

namespace elements {
    template<Page page_from, Page page_to>
    class PageChangerButton final : public StaticTouchableElement<page_from, Page>, UITracker {
    public:
        explicit PageChangerButton(UIManager& manager) :
            StaticTouchableElement<page_from, Page>(
        manager.current_page,
        *manager.texture_manager.get_change_page_button_texture(),
        PositionManager::get_change_page_button_position(),
        [](Page &page, MousePos) {
            if (page == page_from) { page = page_to; }
        }
        ),
            UITracker(manager) {
        }
    };

    using OpenConfigSettingsFromStartSettingButton = PageChangerButton<Page::START_SETTING, Page::CONFIG_SETTINGS>;
    using BackToStartSettingsFromConfigSettingsButton = PageChangerButton<Page::CONFIG_SETTINGS, Page::START_SETTING>;
}

#endif //PAGECHANGERBUTTON_H
