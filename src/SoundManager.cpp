#include "SoundManager.hpp"
#include <iostream>
using namespace std;

SoundManager::SoundManager() {
}

SoundManager::~SoundManager() {

}

void SoundManager::playSound(int id)
{
    if (id == 0)
    {
        buffer.loadFromFile("assets/audio/menu.wav");
        sound.setBuffer(buffer);
        sound.setVolume(80);
        sound.play();
        cout << "Tocando musica do menu" << endl;
    }
    if (id == 1)
    {
        buffer.loadFromFile("assets/audio/gameover.wav");
        sound.setBuffer(buffer);
        sound.setVolume(80);
        sound.play();
        cout << "Tocando gameover" << endl;
    }

    if (id == 2)
    {
        buffer.loadFromFile("assets/audio/background.wav");
        sound.setBuffer(buffer);
        sound.setVolume(80);
        sound.play();
        sound.setLoop(true);
    }

    if(id == 3)
    {
        buffer.loadFromFile("assets/audio/boom.wav");
        sound.setBuffer(buffer);
        sound.setVolume(80);
        sound.play();
        cout << "Tocando boom" << endl;
    }
    if(id == 4)
    {
        buffer.loadFromFile("assets/audio/food.wav");
        sound.setBuffer(buffer);
        sound.setVolume(90);
        sound.play();
        cout << "Tocando food" << endl;
    }
}
