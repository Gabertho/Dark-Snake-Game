#include "Game.h"   

//Static functions

//Initializer functions
void Game::initWindow() {

    std::ifstream ifs("Config/window.ini");

    sf::VideoMode window_bounds(800, 600);
    
    std::string title = "None";
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;

    if (ifs.is_open()) {
        std::getline(ifs, title);
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;    
    }

     ifs.close();

     this->window = new sf::RenderWindow(window_bounds, title);
     this->window->setFramerateLimit(framerate_limit);
     this->window->setVerticalSyncEnabled(vertical_sync_enabled);

}

//Constructors / Destructors

Game::Game() {
    //Creates a SFML window.
    this->initWindow();

}

Game::~Game() {
    delete this->window;
}


//Functions

void Game::updateDt() {
    //Updates the dt variable with the time it takes to update and render one frame. 
    this->dt = this->dtClock.restart().asSeconds();

    system("cls");
    std::cout << this->dt << std::endl;
}

void Game::render() {
    this->window->clear();
    this->window->display();
}

void Game::update() {
    this->updateSFMLEvents();
}

void Game::run() {
    while (this->window->isOpen())
    {
        this->updateDt();
        this->update();
        this->render();
    }
}

void Game::updateSFMLEvents() {
    while (this->window->pollEvent(this->sfEvent))
    {
        if (this->sfEvent.type == sf::Event::Closed) {
            this->window->close();
        }
    }
} 