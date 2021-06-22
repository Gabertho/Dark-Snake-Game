#include "Snake.hpp"
#include <list>
#include <iostream>

Snake::Snake() : m_body(std::list<sf::Sprite>(4))
{
    m_head = --m_body.end();
    m_tail = m_body.begin();
    previously_direction = {64.f, 0.f};
}

Snake::~Snake()
{
}

void Snake::Init(const sf::Texture &texture_tail, const sf::Texture &texture_body, const sf::Texture &texture_head )
{
    float x = 128.f;
    for (auto &piece : m_body)
    {   
        piece.setTexture(texture_body);
        piece.setPosition({x, 128.f});
        x += 64.f;
    }
    m_tail->setTexture(texture_tail);
    m_head->setTexture(texture_head);
}

void Snake::Move(const sf::Vector2f &direction, const sf::Texture &texture_tail, const sf::Texture &texture_body, const sf::Texture &texture_head)
{   
    m_tail->setPosition(m_head->getPosition() + direction);    
    m_head = m_tail;
    ++m_tail;

    if (m_tail == m_body.end())
    {
        m_tail = m_body.begin();
    }
    for (auto &piece : m_body)
    {   
        piece.setTexture(texture_body);
    }
    m_tail->setTexture(texture_tail);
    m_head->setTexture(texture_head);
}

bool Snake::IsOn(const sf::Sprite &other) const
{
    return other.getGlobalBounds().intersects(m_head->getGlobalBounds());
}

void Snake::Grow(const sf::Vector2f &direction)
{
    sf::Sprite newPiece;
    newPiece.setTexture(*(m_body.begin()->getTexture()));
    newPiece.setPosition(m_head->getPosition() + direction);

    m_head = m_body.insert(++m_head, newPiece);
}

void Snake::Degrow(const sf::Vector2f &direction)
{
    sf::Sprite Piece;
    Piece.setPosition(m_head->getPosition());
   for (std::list<sf::Sprite>::iterator it = m_body.begin(); it != m_body.end(); )
{
    if ((*it).getPosition() == Piece.getPosition())
        it = m_body.erase(it);
    else
        ++it;
}
}

bool Snake::IsSelfIntersecting() const
{
    bool flag = false;

    for (auto piece = m_body.begin(); piece != m_body.end(); ++piece)
    {
        if (m_head != piece)
        {
            flag = IsOn(*piece);

            if (flag)
            {
                break;
            }
        }
    }

    return flag;
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto &piece : m_body)
    {
        target.draw(piece);
    }
}