#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <optional>
#include <array_list.h>

int main()
{
    // SETUP
    // ... create the window
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Lab4 (JasonW)");

    // ... the circle object to show the mouse
    float mouse_radius = 100.0f;
    sf::CircleShape mouse_circle(mouse_radius);
    mouse_circle.setFillColor(sf::Color::Transparent);
    mouse_circle.setOutlineColor(sf::Color::White);
    mouse_circle.setOutlineThickness(1.0f);
    mouse_circle.setOrigin(sf::Vector2f(mouse_radius, mouse_radius));

    // The GAME LOOP
    while (window.isOpen())
    {
        // PROCESS EVENTS
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const sf::Event::KeyPressed* keyEvt = event->getIf<sf::Event::KeyPressed>())
            {
                
            }
            else if (const sf::Event::MouseMoved* moveEvt = event->getIf<sf::Event::MouseMoved>())
            {
                mouse_circle.setPosition(sf::Vector2f(moveEvt->position));
            }
        }

        // DRAWING
        window.clear();
        window.draw(mouse_circle);
        window.display();
    }
}