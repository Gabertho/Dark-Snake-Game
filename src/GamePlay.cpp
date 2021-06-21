#include "GamePlay.hpp"
#include "GameOver.hpp"
#include "PauseGame.hpp"

#include <SFML/Window/Event.hpp>

#include <stdlib.h>
#include <time.h>

GamePlay::GamePlay(std::shared_ptr<Context> &context)
    : m_context(context),
      m_score(0),
      m_snakeDirection({64.f, 0.f}),
      m_elapsedTime(sf::Time::Zero),
      m_isPaused(false)
{
    srand(time(nullptr));
}

GamePlay::~GamePlay()
{
}

void GamePlay::Init()
{
    m_context->m_assets->AddTexture(GRASS, "assets/textures/map.jpg", true);
    m_context->m_assets->AddTexture(FOOD, "assets/textures/food.jpg");
    m_context->m_assets->AddTexture(WALL, "assets/textures/wall.jpg", true);
    m_context->m_assets->AddTexture(BODY_UP, "assets/textures/body_up.jpg");
    m_context->m_assets->AddTexture(HEAD_UP, "assets/textures/head_up.jpg");
    m_context->m_assets->AddTexture(TAIL_UP, "assets/textures/tail_up.jpg");
    m_context->m_assets->AddTexture(BODY_DOWN, "assets/textures/body_down.jpg");
    m_context->m_assets->AddTexture(HEAD_DOWN, "assets/textures/head_down.jpg");
    m_context->m_assets->AddTexture(TAIL_DOWN, "assets/textures/tail_down.jpg");
    m_context->m_assets->AddTexture(BODY_LEFT, "assets/textures/body_left.jpg");
    m_context->m_assets->AddTexture(HEAD_LEFT, "assets/textures/head_left.jpg");
    m_context->m_assets->AddTexture(TAIL_LEFT, "assets/textures/tail_left.jpg");
    m_context->m_assets->AddTexture(BODY_RIGHT, "assets/textures/body_right.jpg");
    m_context->m_assets->AddTexture(HEAD_RIGHT, "assets/textures/head_right.jpg");
    m_context->m_assets->AddTexture(TAIL_RIGHT, "assets/textures/tail_right.jpg");

    m_grass.setTexture(m_context->m_assets->GetTexture(GRASS));
    m_grass.setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));

    for (auto &wall : m_walls)
    {
        wall.setTexture(m_context->m_assets->GetTexture(WALL));
    }

    m_walls[0].setTextureRect({0, 0, (int)m_context->m_window->getSize().x, 64});
    m_walls[1].setTextureRect({0, 0, (int)m_context->m_window->getSize().x, 64});
    m_walls[1].setPosition(0, m_context->m_window->getSize().y - 64);

    m_walls[2].setTextureRect({0, 0, 64, (int)m_context->m_window->getSize().y});
    m_walls[3].setTextureRect({0, 0, 64, (int)m_context->m_window->getSize().y});
    m_walls[3].setPosition(m_context->m_window->getSize().x - 64, 0);

    m_food.setTexture(m_context->m_assets->GetTexture(FOOD));
    m_food.setPosition(m_context->m_window->getSize().x / 2, m_context->m_window->getSize().y / 2);

    m_snake.Init(m_context->m_assets->GetTexture(TAIL_RIGHT), m_context->m_assets->GetTexture(BODY_RIGHT), m_context->m_assets->GetTexture(HEAD_RIGHT));


    m_scoreText.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreText.setString("Score : " + std::to_string(m_score));
    m_scoreText.setCharacterSize(15);
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
        else if (event.type == sf::Event::KeyPressed)
        {
            sf::Vector2f newDirection = m_snakeDirection;
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
                newDirection = {0.f, -64.f};
                break;
            case sf::Keyboard::Down:
                newDirection = {0.f, 64.f};
                break;
            case sf::Keyboard::Left:
                newDirection = {-64.f, 0.f};
                break;
            case sf::Keyboard::Right:
                newDirection = {64.f, 0.f};
                break;
            case sf::Keyboard::Escape:
                m_context->m_states->Add(std::make_unique<PauseGame>(m_context));
                break;

            default:
                break;
            }

            if (std::abs(m_snakeDirection.x) != std::abs(newDirection.x) ||
                std::abs(m_snakeDirection.y) != std::abs(newDirection.y))
            {
                m_snakeDirection = newDirection;
            }
        }
    }
}

void GamePlay::Update(sf::Time deltaTime)
{
    if(!m_isPaused)
    {
        m_elapsedTime += deltaTime;

        if (m_elapsedTime.asSeconds() > 0.1)
        {
            for (auto &wall : m_walls)
            {
                if (m_snake.IsOn(wall))
                {
                    m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
                    break;
                }
            }

            if (m_snake.IsOn(m_food))
            {
                m_snake.Grow(m_snakeDirection);

                int x = 0, y = 0;
                x = std::clamp<int>(rand() % m_context->m_window->getSize().x, 64, m_context->m_window->getSize().x - 2 * 64);
                y = std::clamp<int>(rand() % m_context->m_window->getSize().y, 64, m_context->m_window->getSize().y - 2 * 64);

                m_food.setPosition(x, y);
                m_score += 1;
                m_scoreText.setString("Score : " + std::to_string(m_score));
            }
            else
            {   if(m_snakeDirection.x == 0.f && m_snakeDirection.y == -64.f)
                m_snake.Move(m_snakeDirection, m_context->m_assets->GetTexture(TAIL_UP), m_context->m_assets->GetTexture(BODY_UP), m_context->m_assets->GetTexture(HEAD_UP));

                else if(m_snakeDirection.x == 0.f && m_snakeDirection.y == 64.f)
                m_snake.Move(m_snakeDirection, m_context->m_assets->GetTexture(TAIL_DOWN), m_context->m_assets->GetTexture(BODY_DOWN), m_context->m_assets->GetTexture(HEAD_DOWN));

                else if(m_snakeDirection.x == -64.f && m_snakeDirection.y == 0.f)
                m_snake.Move(m_snakeDirection, m_context->m_assets->GetTexture(TAIL_LEFT), m_context->m_assets->GetTexture(BODY_LEFT), m_context->m_assets->GetTexture(HEAD_LEFT));

                else if(m_snakeDirection.x == 64.f && m_snakeDirection.y == 0.f)
                m_snake.Move(m_snakeDirection, m_context->m_assets->GetTexture(TAIL_RIGHT), m_context->m_assets->GetTexture(BODY_RIGHT), m_context->m_assets->GetTexture(HEAD_RIGHT));
            }

            if (m_snake.IsSelfIntersecting())
            {
                m_context->m_states->Add(std::make_unique<GameOver>(m_context), true);
            }

            m_elapsedTime = sf::Time::Zero;
        }
    }
}

void GamePlay::Draw()
{
    m_context->m_window->clear();
    m_context->m_window->draw(m_grass);

    for (auto &wall : m_walls)
    {
        m_context->m_window->draw(wall);
    }
    m_context->m_window->draw(m_food);
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(m_scoreText);

    m_context->m_window->display();
}

void GamePlay::Pause()
{
    m_isPaused = true;
}

void GamePlay::Start()
{
    m_isPaused = false;
}
