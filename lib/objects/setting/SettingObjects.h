//
// Created by Марсель on 03.08.2025.
//

#ifndef SETTINGOBJECTS_H
#define SETTINGOBJECTS_H

#include "config/Config.h"
#include "objects/Object.h"


class SettingObjects final : public Object {
public:
    using SettingCallBack = std::function<void(Config&)>;

private:
    SettingCallBack callback;
    sf::Vector2f position_scale;
    bool touched = false;
public:

    SettingObjects(
        const std::shared_ptr<sf::Texture>& base_texture,
        const std::string&  text,
        const sf::Font& font,
        sf::Vector2f scale,
        SettingCallBack callback);

    void render(sf::RenderWindow &window) const override;

    void touch(Config& config);

    void touch_alternative();
};



#endif //SETTINGOBJECTS_H
