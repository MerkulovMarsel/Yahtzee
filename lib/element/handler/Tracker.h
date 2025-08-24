//
// Created by Марсель on 21.08.2025.
//

#ifndef TRACKER_H
#define TRACKER_H
#include "UIManger/UIManager.h"
#include <optional>

namespace elements {
    using MousePos = const std::optional<sf::Vector2f>&;

    class UITracker {
    public:
        explicit UITracker(const UIManager& manager) {
            manager.add();
        }
    };
}

#endif //TRACKER_H
