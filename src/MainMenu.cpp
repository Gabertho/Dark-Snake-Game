#include "MainMenu.hpp"
#include "GamePlay.hpp"
#include "SoundManager.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

bool MainMenu::m_isPlaying = false;

MainMenu::MainMenu(std::shared_ptr<Context> &context)
    : m_context(context), m_isPlayButtonSelected(true),
      m_isPlayButtonPressed(false), m_isExitButtonSelected(false),
      m_isExitButtonPressed(false)
      
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Music()
{
    if(!m_isPlaying)
    {
    SoundManager sound;
    sound.playSound(0);
    m_isPlaying = true; 
    }  
}

void MainMenu::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/Melted Monster.ttf");
    m_context->m_assets->AddFont(TITLE, "assets/fonts/Zombie_Holocaust.ttf");
    m_context->m_assets->AddTexture(BACKGROUND, "assets/textures/dark-texture.jpg");

    //Background;
    sf::Texture background;
    s_background.setTexture(m_context->m_assets->GetTexture(BACKGROUND));
    s_background.setPosition(0,0);

    // Title
    m_gameTitle.setFont(m_context->m_assets->GetFont(TITLE));
    m_gameTitle.setString("Dark Snake Game");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
                          m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 4.2,
                            m_context->m_window->getSize().y / 2 - 400.f);
    m_gameTitle.setCharacterSize(200);

    // Play Button
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setString("Play");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
                           m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(m_context->m_window->getSize().x / 2.2,
                             m_context->m_window->getSize().y / 2 - 50.f);
    m_playButton.setCharacterSize(100);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
                           m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2.2,
                             m_context->m_window->getSize().y / 2 + 100.f);
    m_exitButton.setCharacterSize(100);
}

void MainMenu::ProcessInput()
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
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!m_isPlayButtonSelected)
                {
                    m_isPlayButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_isExitButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isPlayButtonPressed = false;
                m_isExitButtonPressed = false;

                if (m_isPlayButtonSelected)
                {
                    m_isPlayButtonPressed = true;
                }
                else
                {
                    m_isExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void MainMenu::Update(sf::Time deltaTime)
{
    if(m_isPlayButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Black);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::White);
        m_playButton.setFillColor(sf::Color::Black);
    }
    
    if(m_isPlayButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if(m_isExitButtonPressed)
    {
        m_context->m_window->close();
    }
    
}

void MainMenu::Draw()
{
    m_context->m_window->draw(s_background);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();

}
