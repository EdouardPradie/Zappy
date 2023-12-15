/*
** EPITECH PROJECT, 2023
** gui
** File description:
** FrequencyPanel
*/

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cstddef>
#include <vector>
#include <zappy/GuiClient/GuiClient.hpp>
#include <zappy/HUD/FrequencyPanel.hh>

// Constructor && Destructor

zappy::FrequencyPanel::FrequencyPanel()
{
    m_buttons.emplace_back("<", false);
    m_buttons.emplace_back(">", true);
    m_texts[0].m_str = "Frequency";
    m_texts[1].m_str = "50";
    m_texts[2].m_str = "200";
    m_texts[3].m_str = "500";
    m_shape.setSize({500, 5});
    m_shape.setFillColor({31, 31, 31, 255});
}

// Methods

void zappy::FrequencyPanel::draw(sf::RenderWindow &window, sf::Text &text)
{
    unsigned int size = text.getCharacterSize();

    text.setCharacterSize(30);
    text.setFillColor(m_color);
    setBox(text);
    setPosition(window);
    text.setString(m_texts[0].m_str);
    text.setPosition(m_texts[0].m_position);
    window.draw(text);
    text.setCharacterSize(40);
    if (m_frequency_index < 1)
        m_frequency_index = 3;
    if (m_frequency_index > 3)
        m_frequency_index = 1;
    text.setString(m_texts[m_frequency_index].m_str);
    text.setPosition(m_texts[m_frequency_index].m_position);
    window.draw(text);
    for (auto &button : m_buttons)
        button.draw(window, text);
    window.draw(m_shape);
    text.setCharacterSize(size);
}

void zappy::FrequencyPanel::setPosition(sf::RenderWindow &window)
{
    sf::Vector2f size = window.getView().getSize();
    sf::Vector2f button_pos_1{};
    sf::Vector2f button_pos_2{};

    m_texts[0].m_position = {size.x / 10 * 7, size.y / 10};
    m_shape.setPosition(m_texts[0].m_position.x, m_texts[0].m_position.y + 35.F);
    button_pos_1.x = m_texts[0].m_position.x + 70.F;
    button_pos_1.y = m_texts[0].m_position.y + 40.F;
    m_buttons[0].setPosition(button_pos_1);
    button_pos_2.x = m_texts[0].m_position.x + 170.F;
    button_pos_2.y = m_texts[0].m_position.y + 40.F;
    m_buttons[1].setPosition(button_pos_2);
    for (auto &text : m_texts) {
        if (text.m_str != m_texts[0].m_str) {
            text.m_position.x = m_texts[0].m_position.x + 120.F - (text.m_box.width / 2);
            text.m_position.y = m_texts[0].m_position.y + 40.F;
        }
    }
}

void zappy::FrequencyPanel::manageEvent(sf::RenderWindow &window, sf::View &view, sf::Event &event,
                                        std::vector<std::string> &command_to_send)
{
    static const std::array<std::string, 3> tab_of_value{"50", "200", "500"};
    for (auto &button : m_buttons)
        button.manageEvent(window, view, event, m_frequency_index);

    if (m_frequency_index != m_old_index) {
        if (m_frequency_index < 1)
            m_frequency_index = 3;
        if (m_frequency_index > 3)
            m_frequency_index = 1;
        command_to_send.clear();
        command_to_send.emplace_back("sst " + std::string{tab_of_value[m_frequency_index - 1]} +
                                     "\n");
        m_old_index = m_frequency_index;
    }
}

void zappy::FrequencyPanel::setBox(sf::Text &text)
{
    for (auto &m_text : m_texts) {
        text.setString(m_text.m_str);
        m_text.m_box = text.getGlobalBounds();
    }
}
