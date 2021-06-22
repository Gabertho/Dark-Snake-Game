#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>

#include "AssetMan.hpp"
#include "StateMan.hpp"

enum AssetID
{
    MAIN_FONT = 0,
    GRASS,
    OBSTACLE,
    FOOD,
    WALL,
    BODY_UP, 
    HEAD_UP, 
    TAIL_UP,
    BODY_DOWN, 
    HEAD_DOWN, 
    TAIL_DOWN,
    BODY_RIGHT, 
    HEAD_RIGHT, 
    TAIL_RIGHT,
    BODY_LEFT, 
    HEAD_LEFT, 
    TAIL_LEFT,
    SNAKE
};

struct Context
{
    std::unique_ptr<Engine::AssetMan> m_assets;
    std::unique_ptr<Engine::StateMan> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;

    Context()
    {
        m_assets = std::make_unique<Engine::AssetMan>();
        m_states = std::make_unique<Engine::StateMan>();
        m_window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
private:
    std::shared_ptr<Context> m_context;
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

public:
    Game();
    ~Game();

    void Run();
};