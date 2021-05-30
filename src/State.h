#ifndef STATE_H
#define STATE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp> 
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#

class State{
    public:
        State();
        virtual ~State();

        virtual void update() = 0;
        virtual void render() = 0;
        
    private:
        std::vector<sf::Texture> textures;

};

#endif