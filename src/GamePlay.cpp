#include "GamePlay.hpp"

#include <SFML/Window/Event.hpp>

GamePlay::GamePlay(std::shared_ptr<Context> &context) : m_context(context)
{
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(GRASS, "/home/gabriel/Downloads/Projeto AED1 git/ProjetoAED1/assets/textures/grass.png", true);
    m_context->m_assets->AddTexture(FOOD, "/home/gabriel/Downloads/Projeto AED1 git/ProjetoAED1/assets/textures/food.png");
    m_context->m_assets->AddTexture(WALL, "/home/gabriel/Downloads/Projeto AED1 git/ProjetoAED1/assets/textures/wall.png", true);
    m_context->m_assets->AddTexture(SNAKE, "/home/gabriel/Downloads/Projeto AED1 git/ProjetoAED1/assets/textures/snake.png");

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
}

void GamePlay::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);
    m_context->m_window->display();
}
void GamePlay::Pause()
{
}

void GamePlay::Start()
{
}
