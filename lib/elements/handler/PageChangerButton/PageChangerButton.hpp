//
// Created by Марсель on 21.08.2025.
//

#ifndef PAGECHANGERBUTTON_H
#define PAGECHANGERBUTTON_H

#include "UIManger/ElementsTypes/ElementsTypes.hpp"
#include "UIManger/UIManager.hpp"
#include "elements/base/general/StaticTouchable/StaticTouchableElement.hpp"
#include "UIManger/PositionManger/PositionManager.hpp"
#include "elements/handler/Tracker.hpp"



namespace elements {
    template<Page page_from, Page page_to>
    class PageChangerButton final : public StaticTouchableElement<Page>,
                                    public UITracker {
    public:
        bool enable(const Page current_page) const noexcept override {
            return current_page == page_from || current_page == page_to;
        }

        explicit PageChangerButton(UIManager& manager) :
            StaticTouchableElement<Page>(
        manager.current_page,

        { .texture = manager.texture_manager.get_change_page_button_texture(),
        .position = PositionManager::get_change_page_button_position()},

        { .touch_callback = [](Page &page, MousePos) {
            if (page == page_from) { page = page_to; }
            else if (page == page_to) { page = page_from; }
        }}),

            UITracker(manager) {
        }
    };

    using OpenConfigSettingsFromStartSettingButton = PageChangerButton<Page::START_SETTING, Page::CONFIG_SETTINGS>;
}

#endif //PAGECHANGERBUTTON_H
