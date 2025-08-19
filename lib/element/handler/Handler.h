//
// Created by Марсель on 17.08.2025.
//

#ifndef HANDLER_H
#define HANDLER_H
#include "core/modes/classic/ClassicGame.h"
#include "core/modes/coundown/CountDownGame.h"
#include "core/modes/race/RaceGame.h"
#include "core/modes/speed/SpeedGame.h"
#include "core/modes/test/TestGame.h"
#include "element/Element.h"


namespace elements {
    using Page = Config::Page;
    using GameMode = Config::GameMode;
    using TextTypes = info::TextTypes;
    using MousePos = const std::optional<sf::Vector2f>&;

    template<Page page>
    class BackGround final : public StaticElement<page> {
    public:
        explicit BackGround(const Config& config) :
        StaticElement<page>(
            *config.get_background_texture(page),
            Config::get_background_position()) {}
    };

    using StartSettingsBackGround   = BackGround<Page::START_SETTING>;
    using ConfigSettingsBackGround  = BackGround<Page::CONFIG_SETTINGS>;
    using GameBackGround            = BackGround<Page::GAME_PLAYING>;
    using GameOverBackGround        = BackGround<Page::GAME_OVER>;

    // template<TextTypes text_type>
    // class InfoTextElement final : public StaticElement<static_cast<Page>(text_type)> {
    // public:
    //     explicit InfoTextElement(const Config& config) :
    //     StaticElement<static_cast<Page>(text_type)>(
    //             , config.get_info_text_position(text_type)) {}
    // };


    template<Page page_from, Page page_to>
    class PageChangerButton final : public StaticTouchableElement<page_from, Page> {
    public:
        explicit PageChangerButton(Config& config) :
        StaticTouchableElement<page_from, Page>(
            config.current_page,
            *config.get_change_page_button_texture(),
            Config::get_change_page_button_position(),
            [](Page& page, MousePos) { if (page == page_from) { page = page_to; } }
        ) {}
    };

    using OpenConfigSettingsFromStartSettingButton = PageChangerButton<Page::START_SETTING, Page::CONFIG_SETTINGS>;
    using BackToStartSettingsFromConfigSettingsButton = PageChangerButton<Page::CONFIG_SETTINGS, Page::START_SETTING>;



    // using ChooseGameMoodTextElement      = InfoTextElement<TextTypes::CHOSE_GAME_MODE>;
    // using SettingHeadTextElement         = InfoTextElement<TextTypes::SETTING_HEAD>;
    // using PLayerCountTextElement         = InfoTextElement<TextTypes::PLAYER_COUNT>;
    // using DiceCountTextElement           = InfoTextElement<TextTypes::DICE_COUNT>;
    // using RollCountTextElement           = InfoTextElement<TextTypes::ROLL_COUNT>;
    // using CategoriesTextElement          = InfoTextElement<TextTypes::CATEGORIES>;
    // using PlayersNamesTextElement        = InfoTextElement<TextTypes::PLAYERS_NAMES>;
    // using GameOverPlayersNameTextElement = InfoTextElement<TextTypes::GAME_OVER_PLAYERS_NAMES>;



    using StartGameInfo = std::tuple<std::unique_ptr<Game>,GameConfig::GameState, Page>;
    using SetGameModeButton = StaticTouchableElement<Page::START_SETTING, StartGameInfo>;

    template<GameMode mode>
    void set_game_mode(StartGameInfo& game_info);

    template<Config::PlayerCount count>
    class SetPlayerCountButton final : public DynamicTouchableElement<Page::CONFIG_SETTINGS, std::size_t> {
    public:
        explicit SetPlayerCountButton(Config& config) :
        DynamicTouchableElement(
            config.game_config.game_state.players_count,
            *config.get_player_count_button_texture(count),
            Config::get_count_player_button_position(count),
            [] (std::size_t& current_count, MousePos)
            {current_count = static_cast<std::size_t>(count); },
            [](sf::Sprite& sprite, const std::size_t& current_count, bool) {
                if (current_count == static_cast<std::size_t>(count)) {
                    sprite.setColor(TOUCH_COLOR);
                } else {
                    sprite.setColor(NORMAL_COLOR);
                }
            }) {}
    };

    using SinglePlayerButton = SetPlayerCountButton<Config::PlayerCount::SINGLE>;
    using OneVsOnePlayerButton = SetPlayerCountButton<Config::PlayerCount::ONE_VS_ONE>;

    template<Config::SlidersType slider_type>
    void integral_slider_touch_cb(std::size_t& state, MousePos position);

    template<Config::SlidersType slider_type>
    void integral_slider_update( sf::Sprite& sprite,const std::size_t& state, bool);


    template<Config::SlidersType sliders_type>
    class IntegerSlider final : public DynamicTouchableElement<Page::CONFIG_SETTINGS, std::size_t> {
        sf::Sprite thumb_sprite;
    public:
        explicit IntegerSlider(Config& config) :
        DynamicTouchableElement(
            config.get_slider_state(sliders_type),
            *config.get_slider_track_texture(sliders_type),
            sf::Vector2f(0.,0.),
            integral_slider_touch_cb<sliders_type>,
            integral_slider_update<sliders_type>
        ) {
            thumb_sprite.setTexture(*config.get_slider_thumb_texture(sliders_type));
            thumb_sprite.setPosition(config.get_slider_position(sliders_type));
        }

        [[nodiscard]] sf::FloatRect get_sprite_bounds() const noexcept override {
            return thumb_sprite.getGlobalBounds();
        }

        void render(sf::RenderTarget& window) const override {
            window.draw(thumb_sprite);
            Element::render(window);
        }
    };

    using DIceCountSlider = IntegerSlider<Config::SlidersType::DiceCountSlider>;

    // definitions
    template<GameMode mode>
    void set_game_mode(StartGameInfo& game_info) {
        switch (mode) {
            case GameMode::CLASSIC : {
                std::get<0>(game_info) = std::make_unique<Game>(ClassicGame(std::get<1>(game_info)));
                break;
            }
            case GameMode::COUNT_DOWN : {
                std::get<0>(game_info) = std::make_unique<Game>(CountDownGame(std::get<1>(game_info)));
                break;
            }
            case GameMode::RACE: {
                std::get<0>(game_info) = std::make_unique<Game>(RaceGame(std::get<1>(game_info)));
                break;
            }
            case GameMode::SPEED: {
                std::get<0>(game_info) = std::make_unique<Game>(SpeedGame(std::get<1>(game_info)));
                break;
            }
            default: {
                std::get<0>(game_info) = std::make_unique<Game>(TestGame(std::get<1>(game_info)));
            }
        }

        std::get<2>(game_info) = Page::GAME_PLAYING;
    }

    template<Config::SlidersType slider_type>
    void integral_slider_touch_cb(std::size_t &state, MousePos position) {
        constexpr std::size_t cells_count = static_cast<std::size_t>(slider_type);
        const float x_start = Config::get_slider_position(slider_type).x;
        const std::size_t lowest_value = Config::get_slider_lowest_value(slider_type);
        const float cells_size = Config::get_slider_size(slider_type) / static_cast<float>(cells_count);
        const float mouse_x = position->x - x_start;
        state = lowest_value + static_cast<std::size_t>(mouse_x / cells_size);
    }

    template<Config::SlidersType slider_type>
    void integral_slider_update(sf::Sprite &sprite, const std::size_t &state, bool) {
        constexpr std::size_t cells_count = static_cast<std::size_t>(slider_type);
        const float cells_size = Config::get_slider_size(slider_type) / static_cast<float>(cells_count);
        const float x_lowest_value = Config::get_track_lowest_value_position(slider_type).x;
        const std::size_t lowest_value = Config::get_slider_lowest_value(slider_type);
        const float x = x_lowest_value + cells_size * (state - lowest_value);
        const float y = Config::get_track_lowest_value_position(slider_type).y;
        sprite.setPosition(x, y);
    }

}
struct Handler {
    using Elements = std::vector<Element*>;

    elements::StartSettingsBackGround start_settings_back_ground;
    elements::ConfigSettingsBackGround config_settings_back_ground;
    elements::GameBackGround game_back_ground;
    elements::GameOverBackGround game_over_back_ground;

    elements::OpenConfigSettingsFromStartSettingButton config_from_start_button;
    elements::BackToStartSettingsFromConfigSettingsButton back_to_start_button;

    elements::SinglePlayerButton single_player_button;
    elements::OneVsOnePlayerButton one_vs_one_player_button;

    elements::DIceCountSlider dice_count_slider;

    explicit Handler(Config& config, Elements& elements) :
        start_settings_back_ground(config),
        config_settings_back_ground(config),
        game_back_ground(config),
        game_over_back_ground(config),
        config_from_start_button(config),
        back_to_start_button(config),
        single_player_button(config),
        one_vs_one_player_button(config),
        dice_count_slider(config){
        elements.reserve(9);
        elements.emplace_back(&start_settings_back_ground);
        elements.emplace_back(&config_settings_back_ground);
        elements.emplace_back(&game_back_ground);
        elements.emplace_back(&game_over_back_ground);
        elements.emplace_back(&config_from_start_button);
        elements.emplace_back(&back_to_start_button);
        elements.emplace_back(&single_player_button);
        elements.emplace_back(&one_vs_one_player_button);
        elements.emplace_back(&dice_count_slider);
    }

};




#endif //HANDLER_H
