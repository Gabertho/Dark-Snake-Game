#pragma once

#include <list>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

class Snake : public sf::Drawable
{
private:
    std::list<sf::Sprite> m_body;
    std::list<sf::Sprite>::iterator m_head;
    std::list<sf::Sprite>::iterator m_tail;
    sf::Vector2f previously_direction;

public:
    Snake();
    ~Snake();

    void Init(const sf::Texture &texture_tail, const sf::Texture &texture_body, const sf::Texture &texture_head);
    void Move(const sf::Vector2f &direction, const sf::Texture &texture_tail, const sf::Texture &texture_body, const sf::Texture &texture_head);
    bool IsOn(const sf::Sprite &other) const;
    void Grow(const sf::Vector2f &direction);
    bool IsSelfIntersecting() const;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};