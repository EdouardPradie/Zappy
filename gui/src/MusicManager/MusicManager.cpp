/*
** EPITECH PROJECT, 2023
** gui
** File description:
** MusicManager
*/

#include <zappy/MusicManager/MusicManager.hh>

// Constructor && Destructor

zappy::MusicManager::MusicManager()
{
    m_music.openFromFile(MUSIC_DAY_1.data());
    m_music.setLoop(true);
    m_music.setVolume(25.0F);
    m_music.play();
}

// Methods

void zappy::MusicManager::fade()
{
    float volume = m_music.getVolume();

    if (m_fade_in && m_clock.getElapsedTime().asSeconds() > 0.1F) {
        volume -= 1.F;
        if (volume <= 0) {
            m_fade_in = false;
            m_fade_out = true;
            m_music.pause();
            m_music.openFromFile(m_music_path);
            m_music.play();
        } else
            m_music.setVolume(volume);
        m_clock.restart();
    }
    if (m_fade_out && m_clock.getElapsedTime().asSeconds() > 0.1F) {
        volume += 1.F;
        if (volume >= 25.F)
            m_fade_out = false;
        else
            m_music.setVolume(volume);
        m_clock.restart();
    }
}

void zappy::MusicManager::loadNewMusic(const std::string &str)
{
    m_music_path = str;
    m_fade_in = true;
}

void zappy::MusicManager::playMusic()
{
    m_music.play();
}

void zappy::MusicManager::pauseMusic()
{
    m_music.pause();
}
