#pragma once

#include "State.hpp"
#include "Game.hpp"
#include "Snake.hpp"
#include <array>

#include <SFML/Graphics/Sprite.hpp>

class GamePlay: public Engine::State{

public:
    GamePlay(std::shared_ptr<Context> &context);
    ~GamePlay();
 
    void Init() override;
    void ProcessInput() override;
    void Update(sf::Time deltaTime) override;
    void Draw();

           

    void Pause() override;
    void Start() override;

private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_grass;
    sf::Sprite m_food;
    std::array<sf::Sprite, 4> m_walls;
    Snake m_snake;

    sf::Vector2f m_snakeDirection;
    sf::Time m_elapsedTime;

    //todo:
    //added snake

};