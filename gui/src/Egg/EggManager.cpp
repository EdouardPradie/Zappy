/*
** EPITECH PROJECT, 2023
** Egg
** File description:
** EggManager
*/

#include <ios>
#include <zappy/Egg/EggManager.hh>
#include <zappy/Map/Tile.hh>
#include <zappy/Player/Player.hh>

void zappy::EggManager::addEggs(Enw &egg_infos)
{
    m_eggs_infos.push_back(EggInfos{false, false, false, egg_infos.egg_number,
                                    egg_infos.x_tile_coord, egg_infos.y_tile_coord});
}

void zappy::EggManager::eggHatch(Ebo &egg_selected)
{
    int index{-1};

    for (size_t i{0}; i < m_eggs_infos.size(); i++) {
        if (m_eggs_infos[i].egg_number == egg_selected.egg_number) {
            index = static_cast<int>(i);
            break;
        }
    }
    if (index == -1)
        return;
    m_eggs_infos[static_cast<size_t>(index)].is_hatching = true;
    m_eggs_infos[static_cast<size_t>(index)].rect.left = 368;
}

void zappy::EggManager::eggDeath(Edi &egg_infos)
{
    int index{-1};

    for (size_t i{0}; i < m_eggs_infos.size(); i++) {
        if (m_eggs_infos[i].egg_number == egg_infos.egg_number) {
            index = static_cast<int>(i);
            break;
        }
    }
    if (index == -1)
        return;
    if (m_eggs_infos[static_cast<size_t>(index)].is_hatching)
        m_eggs_infos[static_cast<size_t>(index)].is_hatching = false;
    m_eggs_infos[static_cast<size_t>(index)].is_dead = true;
    m_eggs_infos[static_cast<size_t>(index)].rect.left = 304;
}

void zappy::EggManager::eggHatchAnimation(size_t index, zappy::PlayerManager & /* player_manager */)
{
    if (!(m_eggs_infos[index].anim_clock.getElapsedTime().asSeconds() > 1.2F))
        return;
    m_eggs_infos[index].anim_clock.restart();
    if (m_eggs_infos[index].rect.left >= 368 + m_eggs_infos[index].rect.width &&
        !m_eggs_infos[index].reset_hatch_anim) {
        m_eggs_infos[index].reset_hatch_anim = true;
        m_eggs_infos[index].rect.left = 368;
    }
    if (m_eggs_infos[index].rect.left < 368 + m_eggs_infos[index].rect.width)
        m_eggs_infos[index].rect.left += 32;
    else
        m_eggs_infos[index].is_deletable = true;
}

void zappy::EggManager::eggDeathAnimation(size_t index)
{
    if (!(m_eggs_infos[index].anim_clock.getElapsedTime().asSeconds() > 0.5F))
        return;
    m_eggs_infos[index].anim_clock.restart();
    if (m_eggs_infos[index].rect.left < 304 + m_eggs_infos[index].rect.width)
        m_eggs_infos[index].rect.left += 32;
    else if (m_eggs_infos[index].reset_death_anim) {
        m_eggs_infos[index].is_deletable = true;
    } else {
        m_eggs_infos[static_cast<size_t>(index)].rect.left = 304;
        m_eggs_infos[index].reset_death_anim = true;
    }
}

void zappy::EggManager::eggIdleAnimation(size_t index)
{
    if (m_eggs_infos[index].anim_clock.getElapsedTime().asSeconds() < 0.3F)
        return;
    if (m_eggs_infos[index].wait_idle_anim)
        if (m_eggs_infos[index].anim_clock.getElapsedTime().asSeconds() < 2.0F)
            return;
    m_eggs_infos[index].wait_idle_anim = false;
    m_eggs_infos[index].anim_clock.restart();
    if (m_eggs_infos[index].rect.left < 176 + m_eggs_infos[index].rect.width * 3)
        m_eggs_infos[index].rect.left += 32;
    else {
        m_eggs_infos[index].rect.left = 176;
        m_eggs_infos[index].wait_idle_anim = true;
    }
}

void zappy::EggManager::drawEgg(sf::RenderWindow &window, sf::Sprite &sprite,
                                zappy::PlayerManager &player_manager)
{
    if (m_eggs_infos.empty())
        return;
    for (size_t index{0}; index < m_eggs_infos.size(); index++) {
        if (m_eggs_infos[index].is_hatching)
            eggHatchAnimation(index, player_manager);
        else if (m_eggs_infos[index].is_dead)
            eggDeathAnimation(index);
        else
            eggIdleAnimation(index);
        sprite.setOrigin({16, 24});
        sprite.setPosition(
            {static_cast<float>(m_eggs_infos[index].x_tile_coord * TILE_SIZE * SCALING +
                                (TILE_SIZE * SCALING / 2)),
             static_cast<float>(m_eggs_infos[index].y_tile_coord * TILE_SIZE * SCALING +
                                (TILE_SIZE * SCALING / 2))});
        sprite.setTextureRect(m_eggs_infos[index].rect);
        sprite.setScale(2.5F, 2.5F);
        sprite.move(0, -20);
        window.draw(sprite);
        sprite.setOrigin(0, 0);
        sprite.setScale(SCALING, SCALING);
    }
    deleteUseless();
}

void zappy::EggManager::deleteUseless()
{
    if (m_eggs_infos.empty())
        return;
    for (auto iterator = m_eggs_infos.begin(); iterator != m_eggs_infos.end(); iterator++) {
        if (iterator->is_deletable) {
            m_eggs_infos.erase(iterator);
            deleteUseless();
            break;
        }
    }
}
