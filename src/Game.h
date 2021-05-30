#ifndef GAME_H
#define GAME_H

#include "State.h"

class Game {
    public: 
        //Constructors / Destructors
        Game();
        virtual ~Game();

        //Functions
        void update();
        void render();
        void run();
        void updateSFMLEvents();
        void updateDt();


    private:
        //Variables
        sf::RenderWindow *window;
        sf::Event sfEvent;

        float dt; //delta time
        sf::Clock dtClock; 

        //Initializer functions
        void initWindow();
};


#endif