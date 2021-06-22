#pragma once
#include <SFML/Audio.hpp>


class SoundManager {

public:
    SoundManager();
    ~SoundManager();
    void playSound(int id);
private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
};